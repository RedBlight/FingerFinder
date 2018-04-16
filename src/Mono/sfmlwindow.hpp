#ifndef __SFMLWINDOW__
#define __SFMLWINDOW__

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class SfmlWindowControl
{
public:
	VideoMode vm;
	ContextSettings cs;
	RenderWindow* window;
	SfmlWindowControl();
	~SfmlWindowControl();
};

#endif