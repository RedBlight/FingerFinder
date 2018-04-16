#include "stereosetup.hpp"
#include "fingerfinder.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture c1( 1 );
	VideoCapture c2( 2 );
	// þunlarý release yapmam gerektiðini keþfedene kadar
	// kaybettiðim zamanýn ve blue screen hatalarýnýn haddi hesabý yok...
	// programýn sonunda release yapýldýðýnda, her zaman program sonuna eriþilmediðinden yine problem...
	// ama init - release - tekrar init yapýldýðýný sorun yok
	// akýlýmý seveyim :D
	c1.release();
	c2.release();

	VideoCapture camL( 2 );
	if( !camL.isOpened() )
		camL.open( 2 );

	VideoCapture camR( 1 );
	if( !camR.isOpened() )
		camR.open( 1 );

	StereoSetup setup( &camR, &camL );
	StereoMat frame;

	FingerFinder finder;
	StereoFingers fingers;
	RealFingers real;

	char c;
	cout << "Type 'y' to read calibration data from file: " << endl;
	cin >> c;
	if( c == 'y' )
	{
		setup.ClearCalibration();
		setup.ReadFromFile( "stereosetup.yml" );
	}
	else
	{
		setup.Calibrate( 10, Size( 9, 6 ), Size( 15, 15 ) );
		setup.Rectify();
		setup.PrintToFile( "stereosetup.yml" );
	}

	namedWindow( "CamL", WINDOW_AUTOSIZE );
	namedWindow( "CamR", WINDOW_AUTOSIZE );
	namedWindow( "Debug", WINDOW_AUTOSIZE );

	//PointVector pts;
	//pts.push_back( Point2d( 100, 0 ) );
	//pts.push_back( Point2d( 100, 10 ) );
	//pts.push_back( Point2d( 100, 20 ) );
	//pts.push_back( Point2d( 100, 30 ) );
	//pts.push_back( Point2d( 100, 40 ) );
	//pts.push_back( Point2d( 100, 50 ) );
	//pts.push_back( Point2d( 100, 60 ) );
	//pts.push_back( Point2d( 100, 70 ) );
	//pts.push_back( Point2d( 100, 80 ) );
	//pts.push_back( Point2d( 100, 90 ) );
	//pts.push_back( Point2d( 100, 100 ) );

	Mat debug = Mat::zeros( 640, 480, CV_8UC3 );

	cout << "Press 1, 2, 3, 4, 5 for finger modes." << endl;
	cout << "Press R for switching from normal to rectified." << endl;
	cout << "Press E for switching epipolar lines on-off." << endl;

	int mode = 1;
	bool rectified = false;
	bool epipolar = true;

	while( true )
	{
		debug = Mat::zeros( 480, 480, CV_8UC3 );

		
		if( rectified )
		{
			setup.GetRectifiedFrames( frame );
		}
		else
		{
			setup.GetFrames( frame );
		}

		finder.FindFingers( frame, fingers, mode );

		real.clear();
		setup.TriangulatePoints( fingers, real );
		
		finder.DrawHand( frame, real, true, true, true, true );
		setup.DrawDebug( debug, real );

		if( epipolar )
		{
			setup.DrawEpipoplarLines( frame, fingers.FL, CAM_RIGHT, rectified );
			setup.DrawEpipoplarLines( frame, fingers.FR, CAM_LEFT, rectified );
		}

		imshow( "CamL", frame.ML );
		imshow( "CamR", frame.MR );
		imshow( "Debug", debug );
		
		switch( waitKey( 1 ) )
		{
		case '1':
			mode = 1;
			break;

		case '2':
			mode = 2;
			break;

		case '3':
			mode = 3;
			break;

		case '4':
			mode = 4;
			break;

		case '5':
			mode = 5;
			break;

		case 'r': case 'R':
			rectified = !rectified;
			break;

		case 'e': case 'E':
			epipolar = !epipolar;
			break;
		}
	}

	return 0;
}