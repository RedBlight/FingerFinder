#ifndef STEREOSETUP_INCLUDED
#define STEREOSETUP_INCLUDED

#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define TAU			6.283185307
#define PI			3.141592654
#define PI_2		1.570796327
#define PI_180		0.017453293
#define PI_180_T	57.29577951
#define DEG2RAD(x)	x * PI_180
#define RAD2DEG(x)	x * PI_180_T

typedef vector< Point3f > ObjectPoint;
typedef vector< ObjectPoint > ObjectPoints;

typedef vector< Point2f > ImagePoint;
typedef vector< ImagePoint > ImagePoints;

typedef vector< Point2d > PointVector;

enum CameraIndicator{ CAM_LEFT, CAM_RIGHT };

struct StereoCalibrationParams
{
	// samples are checkerboard images
	int sample_n;			// how many sample images used
	Size corner_n;			// how many corners are there along width and height of the sample
	ImagePoints IPL;			// 2D image points L
	ImagePoints IPR;			// 2D image points R
	ObjectPoints OP;		// 3D object points
};

struct StereoCalibrationResult
{
	Size FrameSize;
	Size Unit;				// real size (width & height) of a chessboard image block
	Mat CL;					// camera matrix L
	Mat CR;					// camera matrix R
	Mat DL;					// distance coefficients L
	Mat DR;					// distance coefficients R
	Mat R;					// rotation matrix
	Mat T;					// translation vector
	Mat E;					// essential matrix
	Mat F;					// fundamental matrix
};

struct StereoRectificationResult
{
	Mat RL;					// rectification transform L
	Mat RR;					// rectification transform R
	Mat PL;					// projection matrix L
	Mat PR;					// projection matrix R
	Mat Q;					// disparity to depth
	Mat MLX;				// rectification map L x
	Mat MLY;				// rectification map L y
	Mat MRX;				// rectification map R x
	Mat MRY;				// rectification map R y
};

struct StereoMat
{
	Mat ML;					// mat L
	Mat MR;					// mat R
};

struct StereoFingers
{
	PointVector FL;					// mat L
	PointVector FR;					// mat R
};

//struct Finger
//{
//	Point2i imagePos1;
//	Point2i imagePos2;
//	Point3f realPos;
//};

typedef vector< Point3d > RealFingers;
//typedef vector< Point4d > RealFingersHomo;

class EpipolarLine
{
public:
	double a;
	double b;
	double c;
	EpipolarLine( double a = 1, double b = 1, double c = 1 );
	double GetX( double y );
	double GetY( double x );
};

class StereoSetup
{
public:
	bool isCapturing;
	bool isCalibrated;
	bool isRectified;

	VideoCapture* CamL; // 2
	VideoCapture* CamR; // 1
	Size imgSize;

	StereoCalibrationParams CP;
	StereoCalibrationResult CR;
	StereoRectificationResult RR;

	StereoSetup();
	StereoSetup( VideoCapture* camL, VideoCapture* camR );
	~StereoSetup();

	// how many sample images will be taken
	// how many blocks are there along width and height in chessboard image
	// width & height of a single chessboard rectangle

	void ClearCalibration();
	void Calibrate( int sample_n, Size corner_n, Size unit );
	void Rectify();

	void GetFrames( StereoMat& frames );
	void GetRectifiedFrames( StereoMat& frames );
	void RectifyFrames( StereoMat& frames );

	void DrawEpipoplarLines( StereoMat& frames, PointVector& points, CameraIndicator ci, bool rectified );

	void PrintToFile( string filename );
	void ReadFromFile( string filename );

	void TriangulatePoints( StereoFingers& SF, RealFingers& RF );

	void DrawDebug( Mat& frame, RealFingers& RF );


};

#endif