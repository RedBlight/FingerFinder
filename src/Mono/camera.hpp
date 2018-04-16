#ifndef __WEBCAM__
#define __WEBCAM__

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class CameraControl
{
public:
	VideoCapture* camera;
	void GetFrameTo( Mat& );
	CameraControl( int );
	~CameraControl();
};

#endif