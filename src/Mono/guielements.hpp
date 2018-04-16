#ifndef __GUIELEMENTS__
#define __GUIELEMENTS__

// SFML 2.0
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "fonts.hpp"

using namespace sf;
using namespace std;

class GuiElements
{
public:
	FontControl* fonts;

	int wnd_width;
	int wnd_height;

	RectangleShape screen_limit;

	RectangleShape background_feed1;
	RectangleShape background_feed2;

	RectangleShape btn_f1_fnone;
	RectangleShape btn_f1_foriginal;
	RectangleShape btn_f1_fgrayscale;
	RectangleShape btn_f1_fgaussed;
	RectangleShape btn_f1_fthresholded;

	RectangleShape btn_f2_fnone;
	RectangleShape btn_f2_foriginal;
	RectangleShape btn_f2_fgrayscale;
	RectangleShape btn_f2_fgaussed;
	RectangleShape btn_f2_fthresholded;

	RectangleShape btn_f1_mcontour;
	RectangleShape btn_f1_mhull;
	RectangleShape btn_f1_mfingers;
	RectangleShape btn_f1_mpalm;

	RectangleShape btn_f2_mcontour;
	RectangleShape btn_f2_mhull;
	RectangleShape btn_f2_mfingers;
	RectangleShape btn_f2_mpalm;

	RectangleShape btn_mode1;
	RectangleShape btn_mode2;
	RectangleShape btn_mode3;
	RectangleShape btn_mode4;
	RectangleShape btn_mode5;

	Text txt_none;
	Text txt_original;
	Text txt_grayscale;
	Text txt_gaussed;
	Text txt_thresholded;
	Text txt_contour;
	Text txt_hull;
	Text txt_fingers;
	Text txt_palm;

	Text txt_f1_none;
	Text txt_f1_original;
	Text txt_f1_grayscale;
	Text txt_f1_gaussed;
	Text txt_f1_thresholded;
	Text txt_f1_contour;
	Text txt_f1_hull;
	Text txt_f1_fingers;
	Text txt_f1_palm;

	Text txt_f2_none;
	Text txt_f2_original;
	Text txt_f2_grayscale;
	Text txt_f2_gaussed;
	Text txt_f2_thresholded;
	Text txt_f2_contour;
	Text txt_f2_hull;
	Text txt_f2_fingers;
	Text txt_f2_palm;

	Text txt_mode1;
	Text txt_mode2;
	Text txt_mode3;
	Text txt_mode4;
	Text txt_mode5;

	Text txt_information;

	GuiElements( FontControl*, int, int ); //window width, height

	bool IsBounding( Vector2< int >, RectangleShape& );
	void MakeInfoText( double, bool );
};

#endif