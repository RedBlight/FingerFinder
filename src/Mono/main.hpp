#pragma comment(linker, "/nodefaultlib:MSVCRTD.lib")

// OpenCV 3.0.0 Alpha
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <algorithm>

// SFML 2.0
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>

#include "_mathdef.hpp"

#include "fonts.hpp"
#include "timectrl.hpp"
#include "sfmlwindow.hpp"
#include "display.hpp"
#include "camera.hpp"
#include "opencvsprites.hpp"
#include "vision.hpp"
#include "guicontrol.hpp"
#include "guielements.hpp"



using namespace sf;
using namespace cv;
using namespace std;