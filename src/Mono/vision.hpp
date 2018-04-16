#ifndef __VISION__
#define __VISION__

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "camera.hpp"
#include "_mathdef.hpp"


#define MODE_F1				1
#define MODE_F2				2
#define MODE_F3				3
#define MODE_F4				4
#define MODE_F5				5

#define FEED_NONE			0
#define FEED_ORGINAL		1
#define FEED_GRAYSCALE		2
#define FEED_GAUSSED		3
#define FEED_THRESHOLDED	4

using namespace cv;
using namespace std;

class VisionControl
{
public:
	CameraControl* camera_1;
	CameraControl* camera_2;
	VisionControl( CameraControl*, CameraControl* );

	double Angle( Point& );
	double Norm( Point& );
	vector< double > NormVector( vector< Point >&, Point&, int& );
	vector< double > NormVector( vector< Point >&, Point& );
	void Rotate( vector< Point >&, double angle );
	void Rotate( Point&, double angle );
	void ReverseY( vector< Point >& );
	void ReverseY( Point& );
	Point AveragePoint( vector< Point >& );
	vector< Point > Directional( vector< Point >&, Point&, double );
	void ArrangeDefects( vector< Point >&, vector< Vec4i >& );
	vector< Point > LocalMaximums( vector< Point >&, Point& );
	void SetLength( Point&, double );

	Mat m_original;
	Mat m_grayscale;
	Mat m_gaussed;
	Mat m_thresholded;
	Mat m_contour;
	vector< vector< Point > > contour;
	vector< vector< Point > > hull;
	vector< vector< int > > hull_i;
	vector< vector< Vec4i > > defect;
	vector< Point > fingers;
	vector< Point > fingers_past;
	Point palm;
	double angle;
	bool hand_found;
	int biggest_blob_index;

	void Run( int ); // mode
	Mat GetMat( int, int, bool, bool, bool, bool ); // frame feed, contour, hull, palms, finger
};

#endif