#include "display.hpp"

using namespace sf;
using namespace std;

#define WND this->wnd->window
#define TIMER this->timer
#define FONT this->fonts

DisplayControl::DisplayControl( SfmlWindowControl* wnd, TimeControl* timer, FontControl* fonts, OpencvSprites* sprites, GuiElements* guielem )
{
	this->wnd = wnd;
	this->timer = timer;
	this->fonts = fonts;
	this->sprites = sprites;
	this->guielem = guielem;
}

void DisplayControl::Run()
{
	WND->clear();
// BEGIN DRAW
//************************
	
	WND->draw( guielem->screen_limit );

	WND->draw( guielem->background_feed1 );
	WND->draw( guielem->background_feed2 );

	WND->draw( guielem->btn_f1_fnone );
	WND->draw( guielem->btn_f1_foriginal );
	WND->draw( guielem->btn_f1_fgrayscale );
	WND->draw( guielem->btn_f1_fgaussed );
	WND->draw( guielem->btn_f1_fthresholded );

	WND->draw( guielem->btn_f2_fnone );
	WND->draw( guielem->btn_f2_foriginal );
	WND->draw( guielem->btn_f2_fgrayscale );
	WND->draw( guielem->btn_f2_fgaussed );
	WND->draw( guielem->btn_f2_fthresholded );

	WND->draw( guielem->btn_f1_mcontour );
	WND->draw( guielem->btn_f1_mhull );
	WND->draw( guielem->btn_f1_mfingers );
	WND->draw( guielem->btn_f1_mpalm );

	WND->draw( guielem->btn_f2_mcontour );
	WND->draw( guielem->btn_f2_mhull );
	WND->draw( guielem->btn_f2_mfingers );
	WND->draw( guielem->btn_f2_mpalm );

	WND->draw( guielem->btn_mode1 );
	WND->draw( guielem->btn_mode2 );
	WND->draw( guielem->btn_mode3 );
	WND->draw( guielem->btn_mode4 );
	WND->draw( guielem->btn_mode5 );

	WND->draw( guielem->txt_f1_none );
	WND->draw( guielem->txt_f1_original );
	WND->draw( guielem->txt_f1_grayscale );
	WND->draw( guielem->txt_f1_gaussed );
	WND->draw( guielem->txt_f1_thresholded );
	WND->draw( guielem->txt_f1_contour );
	WND->draw( guielem->txt_f1_hull );
	WND->draw( guielem->txt_f1_fingers );
	WND->draw( guielem->txt_f1_palm );

	WND->draw( guielem->txt_f2_none );
	WND->draw( guielem->txt_f2_original );
	WND->draw( guielem->txt_f2_grayscale );
	WND->draw( guielem->txt_f2_gaussed );
	WND->draw( guielem->txt_f2_thresholded );
	WND->draw( guielem->txt_f2_contour );
	WND->draw( guielem->txt_f2_hull );
	WND->draw( guielem->txt_f2_fingers );
	WND->draw( guielem->txt_f2_palm );

	WND->draw( guielem->txt_mode1 );
	WND->draw( guielem->txt_mode2 );
	WND->draw( guielem->txt_mode3 );
	WND->draw( guielem->txt_mode4 );
	WND->draw( guielem->txt_mode5 );

	WND->draw( guielem->txt_information );

	WND->draw( sprites->sprite[0] );
	WND->draw( sprites->sprite[1] );

//************************
// END DRAW
	WND->display();
}