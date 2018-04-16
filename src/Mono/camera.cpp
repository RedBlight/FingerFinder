#include "camera.hpp"

using namespace cv;
using namespace std;


CameraControl::CameraControl( int device )
{
	this->camera = new VideoCapture( device );
	if( !this->camera->isOpened() )
        this->camera->open( device );
}

CameraControl::~CameraControl( )
{
	delete this->camera;
}

void CameraControl::GetFrameTo( Mat& image )
{
	*(this->camera) >> image;
}