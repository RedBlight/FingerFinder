#include "vision.hpp"

#include <iostream>

using namespace cv;
using namespace std;

VisionControl::VisionControl( CameraControl* camera_1, CameraControl* camera_2 )
{
	this->camera_1 = camera_1;
	this->camera_2 = camera_2;
	this->biggest_blob_index = 0;
	this->angle = 0;
	this->hand_found = false;
}

double VisionControl::Angle( Point& p )
{
	double x = (double)p.x;
	double y = -(double)p.y;
	double a = atan( abs(y) / abs(x) );

	if( x >= 0 )
	{
		if( y >= 0 )
			return a;
		return TAU - a;
	}
	if( y >= 0 )
		return PI - a;
	return PI + a ;
}

double VisionControl::Norm( Point& p )
{
	return sqrt( (double)(p.x * p.x + p.y * p.y) );
}

vector< double > VisionControl::NormVector( vector< Point >& pvec, Point& offset, int& biggest_norm_index )
{
	biggest_norm_index = 0;
	vector< double > norms;
	for( int i=0; i<pvec.size(); ++i )
	{
		norms.push_back( this->Norm( pvec[i] - offset ) );
		biggest_norm_index = ( norms[i] > norms[ biggest_norm_index ] ) ? i : biggest_norm_index;
	}
	return norms;
}

vector< double > VisionControl::NormVector( vector< Point >& pvec, Point& offset )
{
	vector< double > norms;
	for( int i=0; i<pvec.size(); ++i )
	{
		norms.push_back( this->Norm( pvec[i] - offset ) );
	}
	return norms;
}


void VisionControl::Rotate( vector< Point >& pvec, double angle )
{
	double cs = cos( angle );
	double sn = sin( angle );

	for( int i=0; i<pvec.size(); ++i )
	{
		double px = pvec[i].x;
		double py = pvec[i].y;
		pvec[i].x = px * cs - py * sn; 
		pvec[i].y = px * sn + py * cs;
	}
}

void VisionControl::Rotate( Point& p, double angle )
{
	double cs = cos( angle );
	double sn = sin( angle );
	double px = p.x;
	double py = p.y;
	p.x = px * cs - py * sn; 
	p.y = px * sn + py * cs;
}

void VisionControl::ReverseY( vector< Point >& pvec )
{
	for( int i=0; i<pvec.size(); ++i )
	{
		pvec[i].y = 0 - pvec[i].y;
	}
}

void VisionControl::ReverseY( Point& p )
{
	p.y = 0 - p.y;
}

Point VisionControl::AveragePoint( vector< Point >& pvec )
{
	Point avr( 0, 0 );
	if( pvec.size() > 0 )
	{
		for( int i=0; i<pvec.size(); ++i )
		{
			avr += pvec[i];
		}
		avr.x /= (double)pvec.size();
		avr.y /= (double)pvec.size();
	}
	return avr;
}

vector< Point > VisionControl::Directional( vector< Point >& pvec, Point& offset, double length )
{
	vector< Point > dir;
	Point temp;
	double norm;
	double x;
	double y;
	for( int i=0; i<pvec.size(); ++i )
	{
		temp = pvec[i] - offset;
		norm = this->Norm( temp );
		temp *= length;
		dir.push_back( Point( (double)temp.x / norm,(double)temp.y / norm ) );
	}
	return dir;
}

vector< Point > VisionControl::LocalMaximums( vector< Point >& pvec,  Point& offset )
{
	vector< Point > lmax;
	if( pvec.size() < 3 )
	{
		return lmax;
	}

	vector< double > dist_center = this->NormVector( pvec, offset );
	vector< double > dist_near_prev;
	vector< double > dist_near_next;

	int i_p = pvec.size() - 1;
	int i_n = 1;
	for( int i=0; i<pvec.size(); i++ )
	{
		dist_near_prev.push_back( Norm( pvec[i_p] - pvec[i] ) );
		dist_near_next.push_back( Norm( pvec[i_n] - pvec[i] ) );

		i_p = i;
		i_n = ( i_n + 1 ) % pvec.size();
	}
	
	i_p = pvec.size() - 1;
	i_n = 1;
	for( int i=0; i<pvec.size(); ++i )
	{

		if( ( ( dist_center[i] > dist_center[i_p] ) || dist_near_prev[i] > 30 ) && ( ( dist_center[i] > dist_center[i_n] ) || dist_near_next[i] > 30 )  )
		{
			double divide = 1.0;
			Point temp = pvec[i];
			if( dist_near_prev[i] < 30 )
			{
				temp += pvec[i_p];
				divide += 1;
			}
			if( dist_near_next[i] < 30 )
			{
				temp += pvec[i_n];
				divide += 1;
			}
			lmax.push_back( temp * (double)( 1.0 / divide ) );
		}
		i_p = i;
		i_n = (i_n + 1) % pvec.size();
	}

	return lmax;
}

void VisionControl::ArrangeDefects( vector< Point >& contour, vector< Vec4i >& dvec )
{
	double dist = 0;
	double max_dist = 0;
	int max_dist_i = 0;
	int max_dist_j = 0;
	for( int i = 0; i < dvec.size(); ++i )
	{
		for( int j = 0; j < dvec.size(); ++j )
		{
			dist = Norm( contour[ dvec[i][3] ] - contour[ dvec[j][3] ] );
			if( dist > max_dist )
			{
				max_dist = dist;
				max_dist_i = i;
				max_dist_j = j;
			}
		}
	}


}

void VisionControl::SetLength( Point& p, double l )
{
	double norm = Norm( p );
	p *= l;
	p.x /= norm;
	p.y /= norm;
}

Mat VisionControl::GetMat( int camera, int feed, bool contour, bool hull, bool fingers, bool palm  )
{
	Mat result;

	switch( camera )
	{
	case 1:
		switch( feed )
		{
		case FEED_NONE:			result = Mat::zeros( 480, 640, CV_8UC3 );					break;
		case FEED_ORGINAL:		result = this->m_original.clone();							break;
		case FEED_GRAYSCALE:	cvtColor( this->m_grayscale, result, COLOR_GRAY2BGR );		break;
		case FEED_GAUSSED:		cvtColor( this->m_gaussed, result, COLOR_GRAY2BGR );			break;
		case FEED_THRESHOLDED:	cvtColor( this->m_thresholded, result, COLOR_GRAY2BGR );		break;
		}

		if( contour && this->hand_found )
		{
			drawContours( result, this->contour, this->biggest_blob_index, Scalar( 255, 0, 0 ), 3, 8, vector<Vec4i>(), 0, Point() );
		}

		if( hull && this->hand_found )
		{
			drawContours( result, this->hull, this->biggest_blob_index, Scalar( 0, 255, 0 ), 2, 8, vector<Vec4i>(), 0, Point() );
		}

		if( palm && this->hand_found )
		{
			circle( result, this->palm, 50, Scalar( 0, 0, 255 ), 3 );
		}

		if( fingers && this->hand_found )
		{
			for( int i=0; i<this->fingers.size(); ++i )
			{
				circle( result, this->fingers[i], 20, Scalar( 0, 0, 255 ), 2 );
				putText( result, to_string( i ), Point( this->fingers[i].x, this->fingers[i].y ), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar( 100, 100, 255 ), 1, LINE_AA);
			}
		}
	break;
	case 2:
		this->camera_2->GetFrameTo( this->m_original );
		result = this->m_original.clone();
	break;
	}

	return result;
}

void VisionControl::Run( int mode )
{
	#define defectb defect[biggest_blob_index]
	#define contourb contour[biggest_blob_index]
	#define hullb hull[biggest_blob_index]


	// thresholding
	this->camera_1->GetFrameTo( this->m_original );
	cvtColor( this->m_original, this->m_grayscale, COLOR_BGR2GRAY );
	GaussianBlur( this->m_grayscale, this->m_gaussed, Size_<int>( 5, 5 ), 30, 30 );
	threshold( this->m_gaussed, this->m_thresholded, 60, 255, THRESH_BINARY );

	// extra blur and threshold for smoother hand threshold
	blur( this->m_thresholded, this->m_thresholded, Size_<int>( 21, 21 ) );
	threshold( this->m_thresholded, this->m_thresholded, 130, 255, THRESH_BINARY );

	// finding hand edges and convex hull
	this->m_contour = this->m_thresholded.clone();
	findContours( this->m_contour, this->contour, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	hull.clear();
	hull_i.clear();
	defect.clear();
	this->biggest_blob_index = 0;
	for( int i = 0; i < this->contour.size(); i++ )
	{
		this->biggest_blob_index = ( this->contour[i].size() > this->contour[ this->biggest_blob_index ].size() ) ? i : this->biggest_blob_index;

		hull.push_back( vector< Point >() );
		hull_i.push_back( vector< int >() );
		defect.push_back( vector< Vec4i >() );
		convexHull( contour[i], hull[i], false, true );
		convexHull( contour[i], hull_i[i], false, false );
		convexityDefects( contour[i], hull_i[i], defect[i] );
	}
	
	// very basic check if there is a blob found
	if( ( this->contour.size() < 1 ) || ( this->hull.size() < 1 ) || ( this->hull[ this->biggest_blob_index ].size() < 4 )  )
	{
		this->hand_found = false;
		return;
	}
	this->hand_found = true;

	this->fingers.clear();
	this->palm = this->AveragePoint( this->contour[ this->biggest_blob_index ] );
	vector< Point > lmax = this->LocalMaximums( this->hull[ this->biggest_blob_index ], this->palm );


	//defect.clear();
	//defect.push_back( vector< Vec4i >() );
	//convexityDefects( contourb , hullb, defect[0] );





	














	if( mode == MODE_F1 )
	{


		if( lmax.size() < 2 ) // 2
		{
			this->hand_found = false;
			return;
		}

		// find corresponding directions
		vector< Point > dirs_hull = this->Directional( this->hull[ this->biggest_blob_index ], this->palm, 100 );
		vector< Point > dirs_lmax = this->Directional( lmax, this->palm, 100 );

		Point dir_avg = this->AveragePoint( dirs_hull );
		this->SetLength( dir_avg, 100 );

		vector< double > dir_diff = this->NormVector( dirs_lmax, dir_avg );

		// sort from most marginal to less marginal
		for(int i=0; i<dir_diff.size(); ++i)
		{
			for( int j=0; j<dir_diff.size(); ++j )
			{
				if( dir_diff[i] > dir_diff[j] )
				{
					swap( dir_diff[i], dir_diff[j] );
					swap( lmax[i], lmax[j] );
				}
			}
		}

		// select 2
		vector< Point > p_interest;
		p_interest.push_back( lmax[0] );
		p_interest.push_back( lmax[1] );

		// find norms
		Point palm_hull = this->AveragePoint( this->hull[ this->biggest_blob_index ] );
		vector< double > p_interest_norms = this->NormVector( p_interest, palm_hull );

		// sort from far to close
		for(int i=0; i<p_interest_norms.size(); ++i)
		{
			for( int j=0; j<p_interest_norms.size(); ++j )
			{
				if( p_interest_norms[i] > p_interest_norms[j] )
				{
					swap( p_interest_norms[i], p_interest_norms[j] );
					swap( p_interest[i], p_interest[j] );
				}
			}
		}

		this->fingers.push_back( p_interest[ 0 ] );
	}



	else if( mode > 1 )
	{
		vector< int > defect_indices;
		for( int i = 0; i < defectb.size(); ++i )
		{
			defectb[i][3] /= 256.0;
			defect_indices.push_back( i );
		}
		if( *( --(defect_indices.end()) ) < mode  )
			return;

		// sort defect depths from biggest to smallest
		for( int i = 0; i < defectb.size(); ++i )
		{
			for( int j = 0; j < defectb.size(); ++j )
			{
				if( defectb[i][3] > defectb[j][3] )
				{
					swap( defectb[i], defectb[j] );
					swap( defect_indices[i], defect_indices[j] );
				}
			}
		}

		//vector< Vec4i > def_interest;
		//for( int i = 0; i < mode-1; ++i )
		//{
		//	def_interest.push_back( defectb[i] );
		//}

		// sort defects with their first indices, ascending 
		for( int i = 1; i < mode; ++i )
		{
			for( int j = 1; j < mode; ++j )
			{
				if( defect_indices[i] < defect_indices[j] )
				{
					swap( defectb[i], defectb[j] );
					swap( defect_indices[i], defect_indices[j] );
				}
			}
		}

		//vector<  >defect_angles

		vector< Point > possible_fingers; 

		//fingers.push_back( contour[ biggest_blob_index ][ defectb[1][0] ] );
		for( int i = 1; i < mode; ++i )
		{
			possible_fingers.push_back( contour[ biggest_blob_index ][ defectb[i][0] ] );
			possible_fingers.push_back( contour[ biggest_blob_index ][ defectb[i][1] ] );
		}

		fingers = LocalMaximums( possible_fingers, palm ); 










		//if( lmax.size() < mode )
		//{
		//	this->hand_found = false;
		//	return;
		//}

		//// find white area size in 20*20 rectangle around fingers
		//vector< int > finger_areas;
		//uchar* p;
		//for( int i=0; i<lmax.size(); ++i )
		//{
		//	finger_areas.push_back( 0.0 );
		//	int patch_rad = 20;
		//	int x_start = ( lmax[i].x - patch_rad ) % this->m_thresholded.cols;
		//	int y_start = ( lmax[i].y - patch_rad ) % this->m_thresholded.rows;
		//	if( x_start < 0 ) x_start = 0;
		//	if( y_start < 0 ) y_start = 0;
		//	int x_limit = ( lmax[i].x + patch_rad ) % this->m_thresholded.cols;
		//	int y_limit = ( lmax[i].y + patch_rad ) % this->m_thresholded.rows;
		//	for( int iy=y_start; iy<y_limit; ++iy )
		//	{
		//		p = this->m_thresholded.ptr<uchar>( iy );
		//		for( int ix=x_start; ix<x_limit; ++ix )
		//		{
		//			finger_areas[i] += p[ ix ];
		//		}
		//	}
		//}

		//// sort from biggest area to smallest area
		//for(int i=0; i<finger_areas.size(); ++i)
		//{
		//	for( int j=0; j<finger_areas.size(); ++j )
		//	{
		//		if( finger_areas[i] < finger_areas[j] )
		//		{
		//			swap( finger_areas[i], finger_areas[j] );
		//			swap( lmax[i], lmax[j] );
		//		}
		//	}
		//}

		//for( int i=0; i<mode; ++i )
		//{
		//	this->fingers.push_back( lmax[ i ] );
		//}
	}
}

