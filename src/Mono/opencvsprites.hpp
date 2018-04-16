#ifndef __OPENCVSPRITES__
#define __OPENCVSPRITES__

// OpenCV 3.0.0 Alpha
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

// SFML 2.0
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>

#define S_WIDTH				640
#define S_HEIGHT			480

using namespace cv;
using namespace sf;
using namespace std;

class OpencvSprites
{
public:
	vector< Uint8* > pixels;
	vector< Sprite > sprite;
	vector< Texture > texture;
	OpencvSprites();
	~OpencvSprites();
	void Set( int, Mat&, int ); // ( S_ORIGINAL, frame, COLOR_BGR2RGBA )
};

#endif