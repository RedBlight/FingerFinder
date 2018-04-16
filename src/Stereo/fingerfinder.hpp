#ifndef FINGERFINDER_INCLUDED
#define FINGERFINDER_INCLUDED

#include "stereosetup.hpp"

using namespace cv;
using namespace std;

class FingerFinder
{
public:
	StereoMat mOriginal;
	StereoMat mGrayscale;
	StereoMat mGaussed;
	StereoMat mThresholded;
	StereoMat mContour;

	vector< vector< Point > > contourL;
	vector< Point > hullL;
	vector< int > ihullL;
	vector< Vec4i > defectL;

	vector< vector< Point > > contourR;
	vector< Point > hullR;
	vector< int > ihullR;
	vector< Vec4i > defectR;

	Point palmL;
	Point palmR;

	vector< Point > fingerL;
	vector< Point > fingerR;

	int bbiL;
	int bbiR;

	bool handFound;

	double Angle( Point& );
	double Norm( Point& );
	double Norm( Point3d& p );
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

	void FindFingers( StereoMat& frames, StereoFingers& fingers, int mode );
	void DrawHand( StereoMat& frames, RealFingers& RF, bool contour, bool hull, bool fingers, bool palm );
};

#endif