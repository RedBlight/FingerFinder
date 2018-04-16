#ifndef __GUICONTROL__
#define __GUICONTROL__

// SFML 2.0
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "guielements.hpp"
#include "sfmlwindow.hpp"

using namespace sf;
using namespace std;

class GuiControl
{
public:
	int mode_finger;
	int mode_feed1;
	int mode_feed2;
	bool f1_contour;
	bool f1_hull;
	bool f1_fingers;
	bool f1_palm;
	bool f2_contour;
	bool f2_hull;
	bool f2_fingers;
	bool f2_palm;

	bool prev_pressed;

	bool running;

	GuiElements* guielem;
	SfmlWindowControl* window;
	GuiControl( GuiElements*, SfmlWindowControl* );
	void Run();
};

#endif