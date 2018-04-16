#include "stereosetup.hpp"

Mat triangulate_Linear_LS(Mat mat_P_l, Mat mat_P_r, Mat warped_back_l, Mat warped_back_r)
{
    Mat A(4,3,CV_64FC1), b(4,1,CV_64FC1), X(3,1,CV_64FC1), X_homogeneous(4,1,CV_64FC1), W(1,1,CV_64FC1);
    W.at<double>(0,0) = 1.0;
    A.at<double>(0,0) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,0) - mat_P_l.at<double>(0,0);
    A.at<double>(0,1) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,1) - mat_P_l.at<double>(0,1);
    A.at<double>(0,2) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,2) - mat_P_l.at<double>(0,2);
    A.at<double>(1,0) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,0) - mat_P_l.at<double>(1,0);
    A.at<double>(1,1) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,1) - mat_P_l.at<double>(1,1);
    A.at<double>(1,2) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,2) - mat_P_l.at<double>(1,2);
    A.at<double>(2,0) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,0) - mat_P_r.at<double>(0,0);
    A.at<double>(2,1) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,1) - mat_P_r.at<double>(0,1);
    A.at<double>(2,2) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,2) - mat_P_r.at<double>(0,2);
    A.at<double>(3,0) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,0) - mat_P_r.at<double>(1,0);
    A.at<double>(3,1) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,1) - mat_P_r.at<double>(1,1);
    A.at<double>(3,2) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,2) - mat_P_r.at<double>(1,2);
    b.at<double>(0,0) = -((warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,3) - mat_P_l.at<double>(0,3));
    b.at<double>(1,0) = -((warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,3) - mat_P_l.at<double>(1,3));
    b.at<double>(2,0) = -((warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,3) - mat_P_r.at<double>(0,3));
    b.at<double>(3,0) = -((warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,3) - mat_P_r.at<double>(1,3));
    solve(A,b,X,DECOMP_SVD);
    vconcat(X,W,X_homogeneous);
    return X_homogeneous;
}

StereoSetup::StereoSetup()
{
	isCapturing = false;
	isCalibrated = false;
	isRectified = false;
	CamL = nullptr;
	CamR = nullptr;
}

StereoSetup::StereoSetup( VideoCapture* camL, VideoCapture* camR )
{
	isCapturing = true;
	isCalibrated = false;
	isRectified = false;
	CamL = camL;
	CamR = camR;
}

StereoSetup::~StereoSetup()
{
	CamL->release();
	CamR->release();
}

void StereoSetup::ClearCalibration()
{
	isCalibrated = false;
	isRectified = false;

	CP.sample_n = 0;
	CP.corner_n = Size( 0, 0 );
	CP.IPL.clear();
	CP.IPR.clear();
	CP.OP.clear();
	
	CR.FrameSize = Size( 0, 0 );
	CR.Unit = Size( 0, 0 );
}

void StereoSetup::Calibrate( int sample_n, Size corner_n, Size realBlockSize )
{
	cout << "Calibration of stereo setup has started..." << endl
		 << "-> Press SPACE key to take current frames as a sample." << endl
		 << "-> Sample taking process will take " << sample_n << " images in total." << endl
		 << endl;

	ClearCalibration();
	
	namedWindow( "CamL", WINDOW_AUTOSIZE );
	namedWindow( "CamR", WINDOW_AUTOSIZE );
	
	int successful = 0;
	bool foundL;
	bool foundR;
	bool found;
	Mat frameL;
	Mat frameR;
	Mat grayL;
	Mat grayR;
	ImagePoint IPL;
	ImagePoint IPR;

	CP.sample_n = sample_n;
	CP.corner_n = corner_n;

	ObjectPoint sampleObjectPoint;
	for( int i = 0; i < CP.corner_n.area(); ++i )
    {
		sampleObjectPoint.push_back( Point3f( i / CP.corner_n.width, i % CP.corner_n.width, 0.0 ) );
    }

	while( successful < CP.sample_n )
	{
		CamL->operator>>( frameL );
		CamR->operator>>( frameR );
    
		cvtColor( frameL, grayL, COLOR_BGR2GRAY );
        cvtColor( frameR, grayR, COLOR_BGR2GRAY );

		IPL.clear();
		IPR.clear();

		foundL = findChessboardCorners( frameL, CP.corner_n, IPL, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK + CALIB_CB_FILTER_QUADS );
		foundR = findChessboardCorners( frameR, CP.corner_n, IPR, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK + CALIB_CB_FILTER_QUADS );
		found = foundL && foundR;

        if (foundL)
        {
            cornerSubPix( grayL, IPL, Size(4, 4), Size(-1, -1), TermCriteria( TermCriteria::MAX_ITER, 10, 0.1 ) );
			drawChessboardCorners( frameL, CP.corner_n, IPL, foundL );
        }
        if (foundR)
        {
            cornerSubPix( grayR, IPR, Size(4, 4), Size(-1, -1), TermCriteria( TermCriteria::MAX_ITER, 10, 0.1 ) );
			drawChessboardCorners( frameR, CP.corner_n, IPR, foundR );
        }

        imshow( "CamL", frameL );
        imshow( "CamR", frameR );

		if( waitKey( 1 ) == ' ' && found )
		{
			cout << "-> Press SPACE again to take this set as a sample." << endl;
			if( waitKey() == ' ' )
			{
				CP.IPL.push_back( IPL );
				CP.IPR.push_back( IPR );
				CP.OP.push_back( sampleObjectPoint );
				cout << "-> Sample " << ++successful << " has taken, " << CP.sample_n - successful << " samples remaining." << endl;
			}
			else
			{
				cout << "-> Sample discarded." << endl;
			}
			cout << endl;
		}
	}

	cout << "-> Chessboard image sample taking process has finished." << endl
		 << "-> " << successful << " samples have been taken." << endl
		 << endl;
	
	cout << "-> Calibration from samples has started, please wait..." << endl;

	CR.FrameSize = Size( frameL.size() );
	
	destroyWindow( "CamL" );
	destroyWindow( "CamR" );

	double reProjectionError = stereoCalibrate(
		CP.OP,
		CP.IPL, CP.IPR,
		CR.CL, CR.DL,
		CR.CR, CR.DR,
		CR.FrameSize,
		CR.R, CR.T, CR.E, CR.F
	);

	cout << "-> Calibration has finished. Re-projection error = " << reProjectionError << endl
		 << endl;

	isCalibrated = true;
}

void StereoSetup::Rectify()
{
	cout << "Rectification of stereo setup has initialised..." << endl;
	if( !isCalibrated )
	{
		cout << "-> Stereo setup have not been calibrated yet." << endl
			 << "-> It has to be calibrated for rectifying." << endl
			 << "-> Press SPACE to initiate calibration." << endl
			 << endl;
		if( waitKey() == ' ' )
		{
			int sample_n;
			Size corner_n( 0, 0 );
			Size realBlockSize( 0, 0 );
			string input;

			cout << "Enter how many samples should be taken: ";
			cin >> input;
			sample_n = stoi( input );

			cout << "Enter corner amount along the width: ";
			cin >> input;
			corner_n.width = stoi( input );

			cout << "Enter corner amount along the height: ";
			cin >> input;
			corner_n.height = stoi( input );

			cout << "Enter real horizontal distance between corners in mm: ";
			cin >> input;
			realBlockSize.width = stof( input );

			cout << "Enter real vertical distance between corners in mm: ";
			cin >> input;
			realBlockSize.height = stof( input );

			Calibrate( sample_n, corner_n, realBlockSize );

			cout << "-> Continuing on rectification process." << endl
				 << endl;
		}
		else
		{
			cout << "-> Rectification process cancelled." << endl
				 << endl;
			return;
		}
	}

	cout << "-> Rectification has started..." << endl
		 << endl;
	
	stereoRectify(
		CR.CL, CR.DL,
		CR.CR, CR.DR,
		CR.FrameSize,
		CR.R, CR.T,
		
		RR.RL, RR.RR,
		RR.PL, RR.PR,
		RR.Q
	);

	initUndistortRectifyMap(
		CR.CL, CR.DL,
		RR.RL, RR.PL,
		CR.FrameSize,
		CV_32FC1,
		RR.MLX, RR.MLY
	);

	initUndistortRectifyMap(
		CR.CR, CR.DR,
		RR.RR, RR.PR,
		CR.FrameSize,
		CV_32FC1,
		RR.MRX, RR.MRY
	);

	cout << "-> Rectification has finished." << endl
		 << endl;

	isRectified = true;
}

void StereoSetup::GetFrames( StereoMat& frames )
{
	if( isCapturing )
	{
		CamL->operator>>( frames.ML );
		CamR->operator>>( frames.MR );
	}
	else
	{
		cout << "Can not capture images, cameras are not initialised yet." << endl
			 << "Press ANY key to continue..." << endl
			 << endl;
		waitKey();
	}
}

void StereoSetup::GetRectifiedFrames( StereoMat& frames )
{
	if( isRectified )
	{
		StereoMat org;
		GetFrames( org );
		remap( org.ML, frames.ML, RR.MLX, RR.MLY, INTER_LINEAR );
		remap( org.MR, frames.MR, RR.MRX, RR.MRY, INTER_LINEAR );
	}
	else
	{
		cout << "Can not capture rectified images, cameras are not rectified yet." << endl
			 << "Press ANY key to continue..." << endl
			 << endl;
		waitKey();
	}
}

void StereoSetup::RectifyFrames( StereoMat& frames )
{
	if( isRectified )
	{
		Mat fL = frames.ML.clone();
		Mat fR = frames.MR.clone();
		remap( fL, frames.ML, RR.MLX, RR.MLY, INTER_LINEAR );
		remap( fR, frames.MR, RR.MRX, RR.MRY, INTER_LINEAR );
	}
	else
	{
		cout << "Can not capture rectified images, cameras are not rectified yet." << endl
			 << "Press ANY key to continue..." << endl
			 << endl;
		waitKey();
	}
}

void StereoSetup::DrawEpipoplarLines( StereoMat& frames, PointVector& points, CameraIndicator ci, bool rectified )
{
	Mat F;
	Mat img;
	if( ci == CAM_RIGHT ) // soldaki noktalar saða çizgi
	{
		F = CR.F;
		img = frames.MR;
	}
	else // saðdaki noktalar sola çizgi
	{
		F = CR.F.t();
		img = frames.ML;
	}

	for( int i=0; i < points.size(); ++i )
	{
		if( rectified )
		{
			line( img, Point( 0, points[i].y ), Point( CR.FrameSize.width, points[i].y ), Scalar( 200 * (i%2), ((5-(double)i)/5)*250, ((double)i/5)*250 ) );
		}
		else
		{
			double p[] = { points[i].x, points[i].y, 1 };
			Mat x = Mat( Size( 1, 3 ), CV_64F, p );
			Mat u = F * x;
			double a = u.at< double >( 0 );
			double b = u.at< double >( 1 );
			double c = u.at< double >( 2 );
			double x0 = -1.0;
			double x1 = CR.FrameSize.width + 1;
			double y0 = ( - c - a * x0 ) / b;
			double y1 = ( - c - a * x1 ) / b;

			line( img, Point( x0, y0 ), Point( x1, y1 ), Scalar( 200 * (i%2), ((5-(double)i)/5)*250, ((double)i/5)*250 ) );
		}
	}
}

void StereoSetup::PrintToFile( string filename )
{
	FileStorage fs( filename, FileStorage::WRITE );

    fs << "sample_n" << CP.sample_n;
    fs << "corner_n" << CP.corner_n;
    fs << "IPL" << CP.IPL;
    fs << "IPR" << CP.IPR;
    fs << "OP" << CP.OP;

    fs << "FrameSize" << CR.FrameSize;
    fs << "Unit" << CR.Unit;
    fs << "CL" << CR.CL;
    fs << "CR" << CR.CR;
    fs << "DL" << CR.DL;
    fs << "DR" << CR.DR;
    fs << "R" << CR.R;
    fs << "T" << CR.T;
    fs << "E" << CR.E;
    fs << "F" << CR.F;

    fs << "RL" << RR.RL;
    fs << "RR" << RR.RR;
    fs << "PL" << RR.PL;
    fs << "PR" << RR.PR;
    fs << "Q" << RR.Q;
    fs << "MLX" << RR.MLX;
    fs << "MLY" << RR.MLY;
    fs << "MRX" << RR.MRX;
    fs << "MRY" << RR.MRY;

    fs.release();
}

void StereoSetup::ReadFromFile( string filename )
{
	FileStorage fs( filename, FileStorage::READ );

	fs["sample_n"] >> CP.sample_n;
	fs["corner_n"] >> CP.corner_n;
	//fs["IPL"] >> CP.IPL;
	//fs["IPR"] >> CP.IPR;
	//fs["OP"] >> CP.OP;
	
	fs["FrameSize"] >> CR.FrameSize;
	fs["Unit"] >> CR.Unit;
	fs["CL"] >> CR.CL;
	fs["CR"] >> CR.CR;
	fs["DL"] >> CR.DL;
	fs["DR"] >> CR.DR;
	fs["R"] >> CR.R;
	fs["T"] >> CR.T;
	fs["E"] >> CR.E;
	fs["F"] >> CR.F;

	fs["RL"] >> RR.RL;
	fs["RR"] >> RR.RR;
	fs["PL"] >> RR.PL;
	fs["PR"] >> RR.PR;
	fs["Q"] >> RR.Q;
	fs["MLX"] >> RR.MLX;
	fs["MLY"] >> RR.MLY;
	fs["MRX"] >> RR.MRX;
	fs["MRY"] >> RR.MRY;

	isCalibrated = true;
	isRectified = true;

	fs.release();
}

void StereoSetup::TriangulatePoints( StereoFingers& SF, RealFingers& RF )
{
	//for( int i = 0; i < SF.FL.size(); ++i )
	//{
	//	double up =		( CR.R.at< double >( 0, 0 ) - SF.FL[i].x * CR.R.at< double >( 2, 0 ) ) * CR.T.at< double >( 0 );
	//	up +=			( CR.R.at< double >( 0, 1 ) - SF.FL[i].x * CR.R.at< double >( 2, 1 ) ) * CR.T.at< double >( 1 );
	//	up +=			( CR.R.at< double >( 0, 2 ) - SF.FL[i].x * CR.R.at< double >( 2, 2 ) ) * CR.T.at< double >( 2 );

	//	double dw =		( CR.R.at< double >( 0, 0 ) - SF.FL[i].x * CR.R.at< double >( 2, 0 ) ) * SF.FR[i].x;
	//	dw +=			( CR.R.at< double >( 0, 1 ) - SF.FL[i].x * CR.R.at< double >( 2, 1 ) ) * SF.FR[i].y;
	//	dw +=			( CR.R.at< double >( 0, 2 ) - SF.FL[i].x * CR.R.at< double >( 2, 2 ) ) * 1;

	//	double z = up / dw;

	//	RF.push_back( Point3d( SF.FR[i].x * z, SF.FR[i].y * z, z ) );
	//}


	////////////////////////////////////////////////////////////
	//if( SF.FL.size() > 0 )
	//{
	//	Mat SFL = Mat::zeros( SF.FL.size(), 1, CV_64FC2 );
	//	Mat SFR = Mat::zeros( SF.FL.size(), 1, CV_64FC2 );
	//	Mat RFH = Mat::zeros( SF.FL.size(), 1, CV_64FC4 );

	//	double* p;
	//	for( int i = 0; i < SF.FL.size(); ++i )
	//	{
	//		p = SFL.ptr< double >( i );
	//		p[0] = SF.FL[i].x;
	//		p[1] = SF.FL[i].y;

	//		p = SFR.ptr< double >( i );
	//		p[0] = SF.FR[i].x;
	//		p[1] = SF.FR[i].y;
	//	}

	//	triangulatePoints( RR.PL, RR.PR, SFL, SFR, RFH );
	//	//Mat RFH = triangulate_Linear_LS( RR.PL, RR.PR, SFL, SFR );

	//	RF.clear();
	//	for( int i = 0; i < SF.FL.size(); ++i )
	//	{
	//		p = RFH.ptr< double >( i );
	//		RF.push_back( Point3d(
	//			-p[0] / p[3],
	//			-p[1] / p[3],
	//			-p[2] / p[3]
	//		));
	//		cout << p[3] << endl;
	//	}
	//}
	///////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////
	//	//Mat uvPoint = Mat::ones(3,1,DataType<double>::type); //u,v,1
	//	//uvPoint.at<double>(0,0) = 363.; //got this point using mouse callback
	//	//uvPoint.at<double>(1,0) = 222.;
	//	//Mat tempMat, tempMat2;
	//	//double s;
	//	//tempMat = rotationMatrix.inv() * cameraMatrix.inv() * uvPoint;
	//	//tempMat2 = rotationMatrix.inv() * tvec;
	//	//s = 285 + tempMat2.at<double>(2,0); //285 represents the height Zconst
	//	//s /= tempMat.at<double>(2,0);
	//	//cout << "P = " << rotationMatrix.inv() * (s * cameraMatrix.inv() * uvPoint - tvec) << endl;

	//if( SF.FL.size() > 0 )
	//{
	//	Mat uvPoint = Mat::ones(3,1,DataType<double>::type); //u,v,1
	//	uvPoint.at<double>(0,0) = SF.FL[0].x; //got this point using mouse callback
	//	uvPoint.at<double>(1,0) = SF.FL[0].y;
	//	Mat tempMat, tempMat2;
	//	double s;
	//	tempMat = CR.R.inv() * CR.CL.inv() * uvPoint;
	//	tempMat2 = CR.R.inv() * CR.T;
	//	s = 0 + tempMat2.at<double>(2,0); //285 represents the height Zconst
	//	s /= tempMat.at<double>(2,0);
	//	cout << "P = " << CR.R.inv() * (s * CR.CL.inv() * uvPoint - CR.T) << endl;
	//}
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////


	if( SF.FL.size() > 0 )
	{
		double f = 3.85; // focal
		double b = 60.0; // base line
		double px = 3.85 / 640.0; // pixel size in mm

		double d;
		double dt;
		double t;

		double x;
		double y;
		double z;
		
		RF.clear();
		for( int i = 0; i < SF.FL.size(); ++i )
		{
			d = ( SF.FL[i].x - SF.FR[i].x ) * px;
			dt = atan( d / ( 2.0 * f ) );
			t = PI_2 - dt;
			
			z = ( b / 2.0 ) * tan( t );
			x = ( SF.FL[i].x * z ) / f;
			y = ( SF.FL[i].y * z ) / f;


			RF.push_back( Point3d(
				x * px,
				y * px,
				z
			));
		}
	}
	/////////////////////////////////////////////////////////////////
}

void StereoSetup::DrawDebug( Mat& frame, RealFingers& RF )
{
	putText( frame, "Finger", Point( 15, 15 ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
	putText( frame, "X", Point( 75, 15 ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
	putText( frame, "Y", Point( 205, 15 ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
	putText( frame, "Z", Point( 335, 15 ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
	for( int i = 0; i < RF.size(); ++i )
	{
		putText( frame, to_string( i ), Point( 15, 15 + 30*(i+1) ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
		putText( frame, to_string( (int)RF[i].x ), Point( 75, 15 + 30*(i+1) ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
		putText( frame, to_string( (int)RF[i].y ), Point( 205, 15 + 30*(i+1) ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
		putText( frame, to_string( (int)RF[i].z ), Point( 335, 15 + 30*(i+1) ), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar( 120, 120, 255 ), 1, LINE_AA );
	}
}