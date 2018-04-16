#include "guicontrol.hpp"

using namespace sf;
using namespace std;

GuiControl::GuiControl( GuiElements* guielem, SfmlWindowControl* window )
{
	this->guielem = guielem;
	this->window = window;

	this->prev_pressed = false;

	this->mode_finger = 1;
	this->mode_feed1 = 1;
	this->mode_feed2 = 4;
	this->f1_contour = true;
	this->f1_hull = true;
	this->f1_fingers = true;
	this->f1_palm = true;
	this->f2_contour = false;
	this->f2_hull = false;
	this->f2_fingers = false;
	this->f2_palm = false;
	
	this->running = true;
}

void GuiControl::Run()
{
	// handle user input; exit
	Event event;
	while( this->window->window->pollEvent( event ) )
	{
		// ESC PRESSED
		if( event.type == Event::Closed || Keyboard::isKeyPressed( Keyboard::Escape ) )
		{
			this->running = false;
		}

		// MOUSE EVENTS
		if( !Mouse::isButtonPressed( Mouse::Left ) )
		{
			this->prev_pressed = false;
		}
		if( !this->prev_pressed && Mouse::isButtonPressed( Mouse::Left ) )
		{
			this->prev_pressed = true;
			Vector2i mouse_pos = Mouse::getPosition();
			
			// FINGER MODES
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_mode1 ) )
			{
				this->mode_finger = 1;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_mode2 ) )
			{
				this->mode_finger = 2;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_mode3 ) )
			{
				this->mode_finger = 3;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_mode4 ) )
			{
				this->mode_finger = 4;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_mode5 ) )
			{
				this->mode_finger = 5;
			}

			// FEED 1 MODE
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_fnone ) )
			{
				this->mode_feed1 = 0;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_foriginal ) )
			{
				this->mode_feed1 = 1;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_fgrayscale ) )
			{
				this->mode_feed1 = 2;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_fgaussed ) )
			{
				this->mode_feed1 = 3;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_fthresholded ) )
			{
				this->mode_feed1 = 4;
			}

			// FEED 1 MARKS
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_mcontour ) )
			{
				this->f1_contour = !this->f1_contour;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_mhull ) )
			{
				this->f1_hull = !this->f1_hull;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_mfingers ) )
			{
				this->f1_fingers = !this->f1_fingers;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f1_mpalm ) )
			{
				this->f1_palm = !this->f1_palm;
			}

			// FEED 2 MODE
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_fnone ) )
			{
				this->mode_feed2 = 0;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_foriginal ) )
			{
				this->mode_feed2 = 1;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_fgrayscale ) )
			{
				this->mode_feed2 = 2;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_fgaussed ) )
			{
				this->mode_feed2 = 3;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_fthresholded ) )
			{
				this->mode_feed2 = 4;
			}

			// FEED 2 MARKS
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_mcontour ) )
			{
				this->f2_contour = !this->f2_contour;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_mhull ) )
			{
				this->f2_hull = !this->f2_hull;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_mfingers ) )
			{
				this->f2_fingers = !this->f2_fingers;
			}
			if( this->guielem->IsBounding( mouse_pos, this->guielem->btn_f2_mpalm ) )
			{
				this->f2_palm = !this->f2_palm;
			}
		}
	}

	Color in( 100, 100, 100 );
	Color out( 0, 0, 0 );
	
	// Set all of them out first
	guielem->btn_mode1.setFillColor( out );
	guielem->btn_mode2.setFillColor( out );
	guielem->btn_mode3.setFillColor( out );
	guielem->btn_mode4.setFillColor( out );
	guielem->btn_mode5.setFillColor( out );
	
	guielem->btn_f1_fnone.setFillColor( out );
	guielem->btn_f1_foriginal.setFillColor( out );
	guielem->btn_f1_fgrayscale.setFillColor( out );
	guielem->btn_f1_fgaussed.setFillColor( out );
	guielem->btn_f1_fthresholded.setFillColor( out );
	
	guielem->btn_f1_mcontour.setFillColor( out );
	guielem->btn_f1_mhull.setFillColor( out );
	guielem->btn_f1_mfingers.setFillColor( out );
	guielem->btn_f1_mpalm.setFillColor( out );

	guielem->btn_f2_fnone.setFillColor( out );
	guielem->btn_f2_foriginal.setFillColor( out );
	guielem->btn_f2_fgrayscale.setFillColor( out );
	guielem->btn_f2_fgaussed.setFillColor( out );
	guielem->btn_f2_fthresholded.setFillColor( out );
	
	guielem->btn_f2_mcontour.setFillColor( out );
	guielem->btn_f2_mhull.setFillColor( out );
	guielem->btn_f2_mfingers.setFillColor( out );
	guielem->btn_f2_mpalm.setFillColor( out );

	switch( this->mode_finger )
	{
	case 1:		guielem->btn_mode1.setFillColor( in );				break;
	case 2:		guielem->btn_mode2.setFillColor( in );				break;
	case 3:		guielem->btn_mode3.setFillColor( in );				break;
	case 4:		guielem->btn_mode4.setFillColor( in );				break;
	case 5:		guielem->btn_mode5.setFillColor( in );				break;
	}

	switch( this->mode_feed1 )
	{
	case 0:		guielem->btn_f1_fnone.setFillColor( in );			break;
	case 1:		guielem->btn_f1_foriginal.setFillColor( in );		break;
	case 2:		guielem->btn_f1_fgrayscale.setFillColor( in );		break;
	case 3:		guielem->btn_f1_fgaussed.setFillColor( in );			break;
	case 4:		guielem->btn_f1_fthresholded.setFillColor( in );		break;
	}

	switch( this->mode_feed2 )
	{
	case 0:		guielem->btn_f2_fnone.setFillColor( in );			break;
	case 1:		guielem->btn_f2_foriginal.setFillColor( in );		break;
	case 2:		guielem->btn_f2_fgrayscale.setFillColor( in );		break;
	case 3:		guielem->btn_f2_fgaussed.setFillColor( in );			break;
	case 4:		guielem->btn_f2_fthresholded.setFillColor( in );		break;
	}

	if( this->f1_contour )	guielem->btn_f1_mcontour.setFillColor( in );
	if( this->f1_hull )		guielem->btn_f1_mhull.setFillColor( in );
	if( this->f1_fingers )	guielem->btn_f1_mfingers.setFillColor( in );
	if( this->f1_palm )		guielem->btn_f1_mpalm.setFillColor( in );

	if( this->f2_contour )	guielem->btn_f2_mcontour.setFillColor( in );
	if( this->f2_hull )		guielem->btn_f2_mhull.setFillColor( in );
	if( this->f2_fingers )	guielem->btn_f2_mfingers.setFillColor( in );
	if( this->f2_palm )		guielem->btn_f2_mpalm.setFillColor( in );
}