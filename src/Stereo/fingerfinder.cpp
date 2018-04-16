#include "fingerfinder.hpp"

double FingerFinder::Angle( Point& p )
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

double FingerFinder::Norm( Point& p )
{
	return sqrt( (double)(p.x * p.x + p.y * p.y) );
}

double FingerFinder::Norm( Point3d& p )
{
	return sqrt( p.x * p.x + p.y * p.y + p.z * p.z );
}

vector< double > FingerFinder::NormVector( vector< Point >& pvec, Point& offset, int& biggest_norm_index )
{
	biggest_norm_index = 0;
	vector< double > norms;
	for( int i=0; i<pvec.size(); ++i )
	{
		norms.push_back( Norm( pvec[i] - offset ) );
		biggest_norm_index = ( norms[i] > norms[ biggest_norm_index ] ) ? i : biggest_norm_index;
	}
	return norms;
}

vector< double > FingerFinder::NormVector( vector< Point >& pvec, Point& offset )
{
	vector< double > norms;
	for( int i=0; i<pvec.size(); ++i )
	{
		norms.push_back( Norm( pvec[i] - offset ) );
	}
	return norms;
}


void FingerFinder::Rotate( vector< Point >& pvec, double angle )
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

void FingerFinder::Rotate( Point& p, double angle )
{
	double cs = cos( angle );
	double sn = sin( angle );
	double px = p.x;
	double py = p.y;
	p.x = px * cs - py * sn; 
	p.y = px * sn + py * cs;
}

void FingerFinder::ReverseY( vector< Point >& pvec )
{
	for( int i=0; i<pvec.size(); ++i )
	{
		pvec[i].y = 0 - pvec[i].y;
	}
}

void FingerFinder::ReverseY( Point& p )
{
	p.y = 0 - p.y;
}

Point FingerFinder::AveragePoint( vector< Point >& pvec )
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

vector< Point > FingerFinder::Directional( vector< Point >& pvec, Point& offset, double length )
{
	vector< Point > dir;
	Point temp;
	double norm;
	double x;
	double y;
	for( int i=0; i<pvec.size(); ++i )
	{
		temp = pvec[i] - offset;
		norm = Norm( temp );
		temp *= length;
		dir.push_back( Point( (double)temp.x / norm,(double)temp.y / norm ) );
	}
	return dir;
}

vector< Point > FingerFinder::LocalMaximums( vector< Point >& pvec,  Point& offset )
{
	vector< Point > lmax;
	if( pvec.size() < 3 )
	{
		return lmax;
	}

	vector< double > dist_center = NormVector( pvec, offset );
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

void FingerFinder::ArrangeDefects( vector< Point >& contour, vector< Vec4i >& dvec )
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

void FingerFinder::SetLength( Point& p, double l )
{
	double norm = Norm( p );
	p *= l;
	p.x /= norm;
	p.y /= norm;
}

void FingerFinder::FindFingers( StereoMat& frames, StereoFingers& fingers, int mode )
{
	handFound = false;

	mOriginal.ML = frames.ML.clone();
	mOriginal.MR = frames.MR.clone();

	cvtColor( mOriginal.ML, mGrayscale.ML, COLOR_BGR2GRAY );
	cvtColor( mOriginal.MR, mGrayscale.MR, COLOR_BGR2GRAY );

	GaussianBlur( mGrayscale.ML, mGaussed.ML, Size_<int>( 5, 5 ), 30, 30 );
	GaussianBlur( mGrayscale.MR, mGaussed.MR, Size_<int>( 5, 5 ), 30, 30 );

	threshold( mGaussed.ML, mThresholded.ML, 60, 255, THRESH_BINARY );
	threshold( mGaussed.MR, mThresholded.MR, 60, 255, THRESH_BINARY );

	blur( mThresholded.ML, mThresholded.ML, Size_<int>( 21, 21 ) );
	blur( mThresholded.MR, mThresholded.MR, Size_<int>( 21, 21 ) );

	threshold( mThresholded.ML, mThresholded.ML, 130, 255, THRESH_BINARY );
	threshold( mThresholded.MR, mThresholded.MR, 130, 255, THRESH_BINARY );

	mContour.ML = mThresholded.ML.clone();
	mContour.MR = mThresholded.MR.clone();

	findContours( mContour.ML, contourL, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	findContours( mContour.MR, contourR, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	hullL.clear();
	hullR.clear();

	ihullL.clear();
	ihullR.clear();

	defectL.clear();
	defectR.clear();

	bbiL = 0;
	bbiR = 0;

	for( int i = 0; i < contourL.size(); i++ )
		bbiL = ( contourL[i].size() > contourL[ bbiL ].size() ) ? i : bbiL;
	for( int i = 0; i < contourR.size(); i++ )
		bbiR = ( contourR[i].size() > contourR[ bbiR ].size() ) ? i : bbiR;

		// very basic check if there is a blob found
	//if(
	//	( ( contourL.size() < 1 ) || ( hullL.size() < 4 ) )
	//	|| 
	//	( ( contourR.size() < 1 ) || ( hullR.size() < 4 ) )
	//)
	if( ( contourL.size() < 1 ) || ( contourR.size() < 1 )  )
		return;

	convexHull( contourL[ bbiL ], hullL, false, true );
	convexHull( contourR[ bbiR ], hullR, false, true );

	convexHull( contourL[ bbiL ], ihullL, false, false );
	convexHull( contourR[ bbiR ], ihullR, false, false );

	convexityDefects( contourL[ bbiL ], ihullL, defectL );
	convexityDefects( contourR[ bbiR ], ihullR, defectR );

	fingerL.clear();
	fingerR.clear();

	palmL = AveragePoint( contourL[ bbiL ] );
	palmR = AveragePoint( contourR[ bbiR ] );

	vector< Point > lmaxL = LocalMaximums( hullL, palmL );
	vector< Point > lmaxR = LocalMaximums( hullR, palmR );

	if( mode == 1 )
	{
		if( ( lmaxL.size() < 2 ) || ( lmaxR.size() < 2 ) ) // 2
			return;

		vector< Point > dirsHullL = Directional( hullL, palmL, 100 );
		vector< Point > dirsHullR = Directional( hullR, palmR, 100 );

		vector< Point > dirsLmaxL = Directional( lmaxL, palmL, 100 );
		vector< Point > dirsLmaxR = Directional( lmaxR, palmR, 100 );

		Point dirAvgL = AveragePoint( dirsHullL );
		Point dirAvgR = AveragePoint( dirsHullR );

		SetLength( dirAvgL, 100 );
		SetLength( dirAvgR, 100 );

		vector< double > dirDiffL = NormVector( dirsLmaxL, dirAvgL );
		vector< double > dirDiffR = NormVector( dirsLmaxR, dirAvgR );

		// sort from most marginal to less marginal
		for(int i = 0; i < dirDiffL.size(); ++i )
		{
			for( int j = 0; j < dirDiffL.size(); ++j )
			{
				if( dirDiffL[i] > dirDiffL[j] )
				{
					swap( dirDiffL[i], dirDiffL[j] );
					swap( lmaxL[i], lmaxL[j] );
				}
			}
		}
		for( int i = 0; i < dirDiffR.size(); ++i )
		{
			for( int j = 0; j < dirDiffR.size(); ++j )
			{
				if( dirDiffR[i] > dirDiffR[j] )
				{
					swap( dirDiffR[i], dirDiffR[j] );
					swap( lmaxR[i], lmaxR[j] );
				}
			}
		}

		// erase if near edge;
		for( int i = 0; i < lmaxL.size(); ++i )
		{
			if( lmaxL[i].x < 10 || lmaxL[i].x > 630 || lmaxL[i].y < 10 || lmaxL[i].y > 470 )
			{
				lmaxL.erase( lmaxL.begin() + i );
				--i;
			}
		}

		for( int i = 0; i < lmaxR.size(); ++i )
		{
			if( lmaxR[i].x < 10 || lmaxR[i].x > 630 || lmaxR[i].y < 10 || lmaxR[i].y > 470 )
			{
				lmaxR.erase( lmaxR.begin() + i );
				--i;
			}
		}

		if( ( lmaxL.size() < 2 ) || ( lmaxR.size() < 2 ) ) // 2
			return;

		// select 2
		vector< Point > pinterestL;
		vector< Point > pinterestR;

		pinterestL.push_back( lmaxL[0] );
		pinterestR.push_back( lmaxR[0] );

		pinterestL.push_back( lmaxL[1] );
		pinterestR.push_back( lmaxR[1] );

		// find norms
		Point palmHullL = AveragePoint( hullL );
		Point palmHullR = AveragePoint( hullR );

		vector< double > pinterestNormsL = NormVector( pinterestL, palmHullL );
		vector< double > pinterestNormsR = NormVector( pinterestR, palmHullR );

		// sort from far to near
		for(int i=0; i<pinterestNormsL.size(); ++i)
		{
			for( int j=0; j<pinterestNormsL.size(); ++j )
			{
				if( pinterestNormsL[i] > pinterestNormsL[j] )
				{
					swap( pinterestNormsL[i], pinterestNormsL[j] );
					swap( pinterestL[i], pinterestL[j] );
				}
			}
		}
		for(int i=0; i<pinterestNormsR.size(); ++i)
		{
			for( int j=0; j<pinterestNormsR.size(); ++j )
			{
				if( pinterestNormsR[i] > pinterestNormsR[j] )
				{
					swap( pinterestNormsR[i], pinterestNormsR[j] );
					swap( pinterestR[i], pinterestR[j] );
				}
			}
		}

		fingerL.push_back( pinterestL[ 0 ] );
		fingerR.push_back( pinterestR[ 0 ] );

		fingers.FL.clear();
		fingers.FR.clear();

		fingers.FL.push_back( Point2d( fingerL[ 0 ].x, fingerL[ 0 ].y ) );
		fingers.FR.push_back( Point2d( fingerR[ 0 ].x, fingerR[ 0 ].y ) );

		handFound = true;
	}
	else if( mode > 1 )
	{
		vector< int > idefectL;
		vector< int > idefectR;

		for( int i = 0; i < defectL.size(); ++i )
		{
			defectL[ i ][ 3 ] /= 256.0;
			idefectL.push_back( i );
		}
		for( int i = 0; i < defectR.size(); ++i )
		{
			defectR[ i ][ 3 ] /= 256.0;
			idefectR.push_back( i );
		}

		if( *( --(idefectL.end()) ) < mode || *( --(idefectR.end()) ) < mode  )
			return;

		// sort defect depths from biggest to smallest
		for( int i = 0; i < defectL.size(); ++i )
		{
			for( int j = 0; j < defectL.size(); ++j )
			{
				if( defectL[i][3] > defectL[j][3] )
				{
					swap( defectL[i], defectL[j] );
					swap( idefectL[i], idefectL[j] );
				}
			}
		}
		for( int i = 0; i < defectR.size(); ++i )
		{
			for( int j = 0; j < defectR.size(); ++j )
			{
				if( defectR[i][3] > defectR[j][3] )
				{
					swap( defectR[i], defectR[j] );
					swap( idefectR[i], idefectR[j] );
				}
			}
		}

		// sort defects with their first indices, ascending ? only indices from 1 to mode
		for( int i = 1; i < mode; ++i )
		{
			for( int j = 1; j < mode; ++j )
			{
				if( idefectL[i] < idefectL[j] )
				{
					swap( defectL[i], defectL[j] );
					swap( idefectL[i], idefectL[j] );
				}
			}
		}
		for( int i = 1; i < mode; ++i )
		{
			for( int j = 1; j < mode; ++j )
			{
				if( idefectR[i] < idefectR[j] )
				{
					swap( defectR[i], defectR[j] );
					swap( idefectR[i], idefectR[j] );
				}
			}
		}

		vector< Point > pinterestL;
		vector< Point > pinterestR;

		for( int i = 1; i < mode; ++i )
		{
			pinterestL.push_back( contourL[ bbiL ][ defectL[i][0] ] );
			pinterestL.push_back( contourL[ bbiL ][ defectL[i][1] ] );

			pinterestR.push_back( contourR[ bbiR ][ defectR[i][0] ] );
			pinterestR.push_back( contourR[ bbiR ][ defectR[i][1] ] );
		}
		
		if( mode == 2 )
		{
			fingerL = vector< Point >( pinterestL );
			fingerR = vector< Point >( pinterestR );
		}
		else
		{
			fingerL = LocalMaximums( pinterestL, palmL );
			fingerR = LocalMaximums( pinterestR, palmR );
		}

		if( fingerL.size() < mode || fingerR.size() < mode  )
			return;

		fingers.FL.clear();
		fingers.FR.clear();

		for( int i = 0; i < mode; ++i )
		{
			fingers.FL.push_back( Point2d( fingerL[ i ].x, fingerL[ i ].y ) );
			fingers.FR.push_back( Point2d( fingerR[ i ].x, fingerR[ i ].y ) );
		}

		handFound = true;
	}
}

void FingerFinder::DrawHand( StereoMat& frames, RealFingers& RF, bool _contour, bool _hull, bool _fingers, bool _palm  )
{
	if( handFound )
	{
		if( _contour )
		{
			drawContours( frames.ML, contourL, bbiL, Scalar( 255, 0, 0 ), 3, 8, vector<Vec4i>(), 0, Point() );
			drawContours( frames.MR, contourR, bbiR, Scalar( 255, 0, 0 ), 3, 8, vector<Vec4i>(), 0, Point() );
		}
		
		if( _hull )
		{
			vector< vector< Point > > hcL;
			vector< vector< Point > > hcR;
			hcL.push_back( hullL );
			hcR.push_back( hullR );
			drawContours( frames.ML, hcL, 0, Scalar( 0, 255, 0 ), 2, 8, vector<Vec4i>(), 0, Point() );
			drawContours( frames.MR, hcR, 0, Scalar( 0, 255, 0 ), 2, 8, vector<Vec4i>(), 0, Point() );
		}
		
		if( _palm )
		{
			circle( frames.ML, palmL, 50, Scalar( 0, 0, 255 ), 3 );
			circle( frames.MR, palmR, 50, Scalar( 0, 0, 255 ), 3 );
		}

		if( _fingers )
		{
			for( int i = 0; i < fingerL.size(); ++i )
			{
				circle( frames.ML, fingerL[i], 20, Scalar( 0, 0, 255 ), 2 );
				putText( frames.ML, to_string( i ), Point( fingerL[i].x + 20, fingerL[i].y + 20 ), FONT_HERSHEY_COMPLEX_SMALL, 1.3, Scalar( 0, 0, 255 ), 1, LINE_AA );
			}
			for( int i = 0; i < fingerR.size(); ++i )
			{
				circle( frames.MR, fingerR[i], 20, Scalar( 0, 0, 255 ), 2 );
				putText( frames.MR, to_string( i ), Point( fingerR[i].x + 20, fingerR[i].y + 20 ), FONT_HERSHEY_COMPLEX_SMALL, 1.3, Scalar( 0, 0, 255 ), 1, LINE_AA );
			}

			for( int i = 1; i < RF.size(); ++i )
			{
				double dist = abs( Norm( RF[i] - RF[i-1] )  );
				putText( frames.ML, to_string( (int)dist ) + "mm", Point( (fingerL[i].x + fingerL[i-1].x)/2 + 2, (fingerL[i].y + fingerL[i-1].y)/2 + 2 ), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar( 0, 0, 255 ), 1, LINE_AA );
			}

		}
	}
}