#ifndef __DISPLAY__
#define __DISPLAY__

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>

#include "sfmlwindow.hpp"
#include "timectrl.hpp"
#include "fonts.hpp"
#include "opencvsprites.hpp"
#include "guielements.hpp"

using namespace sf;
using namespace std;

class DisplayControl
{
public:
	FontControl* fonts;
	SfmlWindowControl* wnd;
	TimeControl* timer;
	OpencvSprites* sprites;
	GuiElements* guielem;
	DisplayControl( SfmlWindowControl*, TimeControl*, FontControl*, OpencvSprites*, GuiElements* );
	void Run();
};

#endif