#include "guielements.hpp"

using namespace sf;
using namespace std;

GuiElements::GuiElements( FontControl* fonts, int wnd_width, int wnd_height )
{
	this->fonts = fonts;

	this->wnd_width = wnd_width;
	this->wnd_height = wnd_height;

	int left_start = ( wnd_width / 2 ) - 645;

	//RectangleShape screen_limit;
	screen_limit.setSize( Vector2f( 1366, 768 ) );
	screen_limit.setPosition( (wnd_width-1366)/2 , 0 );
	screen_limit.setOutlineThickness( 1 );
	screen_limit.setOutlineColor( Color( 0, 255, 0, 255 ) );
	screen_limit.setFillColor( Color( 0, 0, 0, 0 ) );

	//RectangleShape background_feed1;
	background_feed1.setSize( Vector2f( 640, 480 ) );
	background_feed1.setPosition( left_start , 1 );
	background_feed1.setOutlineThickness( 1 );
	background_feed1.setOutlineColor( Color( 0, 255, 0, 255 ) );

	//RectangleShape background_feed2;
	background_feed2.setSize( Vector2f( 640, 480 ) );
	background_feed2.setPosition( left_start+650 , 1 );
	background_feed2.setOutlineThickness( 1 );
	background_feed2.setOutlineColor( Color( 0, 255, 0, 255 ) );

	//RectangleShape btn_f1_fnone;
	btn_f1_fnone.setSize( Vector2f( 128, 30 ) );
	btn_f1_fnone.setPosition( left_start + 128*0 , 490 );
	btn_f1_fnone.setOutlineThickness( 1 );
	btn_f1_fnone.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_fnone.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_foriginal;
	btn_f1_foriginal.setSize( Vector2f( 128, 30 ) );
	btn_f1_foriginal.setPosition( left_start + 128*1 , 490 );
	btn_f1_foriginal.setOutlineThickness( 1 );
	btn_f1_foriginal.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_foriginal.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_fgrayscale;
	btn_f1_fgrayscale.setSize( Vector2f( 128, 30 ) );
	btn_f1_fgrayscale.setPosition( left_start + 128*2 , 490 );
	btn_f1_fgrayscale.setOutlineThickness( 1 );
	btn_f1_fgrayscale.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_fgrayscale.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_fgaussed;
	btn_f1_fgaussed.setSize( Vector2f( 128, 30 ) );
	btn_f1_fgaussed.setPosition( left_start + 128*3 , 490 );
	btn_f1_fgaussed.setOutlineThickness( 1 );
	btn_f1_fgaussed.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_fgaussed.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_fthresholded;
	btn_f1_fthresholded.setSize( Vector2f( 128, 30 ) );
	btn_f1_fthresholded.setPosition( left_start + 128*4 , 490 );
	btn_f1_fthresholded.setOutlineThickness( 1 );
	btn_f1_fthresholded.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_fthresholded.setFillColor( Color( 0, 0, 0, 255 ) );


	//RectangleShape btn_f2_fnone;
	btn_f2_fnone.setSize( Vector2f( 128, 30 ) );
	btn_f2_fnone.setPosition( left_start+650 + 128*0 , 490 );
	btn_f2_fnone.setOutlineThickness( 1 );
	btn_f2_fnone.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_fnone.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_foriginal;
	btn_f2_foriginal.setSize( Vector2f( 128, 30 ) );
	btn_f2_foriginal.setPosition( left_start+650 + 128*1 , 490 );
	btn_f2_foriginal.setOutlineThickness( 1 );
	btn_f2_foriginal.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_foriginal.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_fgrayscale;
	btn_f2_fgrayscale.setSize( Vector2f( 128, 30 ) );
	btn_f2_fgrayscale.setPosition( left_start+650 + 128*2 , 490 );
	btn_f2_fgrayscale.setOutlineThickness( 1 );
	btn_f2_fgrayscale.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_fgrayscale.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_fgaussed;
	btn_f2_fgaussed.setSize( Vector2f( 128, 30 ) );
	btn_f2_fgaussed.setPosition( left_start+650 + 128*3 , 490 );
	btn_f2_fgaussed.setOutlineThickness( 1 );
	btn_f2_fgaussed.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_fgaussed.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_fthresholded;
	btn_f2_fthresholded.setSize( Vector2f( 128, 30 ) );
	btn_f2_fthresholded.setPosition( left_start+650 + 128*4 , 490 );
	btn_f2_fthresholded.setOutlineThickness( 1 );
	btn_f2_fthresholded.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_fthresholded.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_f1_mcontour;
	btn_f1_mcontour.setSize( Vector2f( 160, 30 ) );
	btn_f1_mcontour.setPosition( left_start + 160*0 , 521 );
	btn_f1_mcontour.setOutlineThickness( 1 );
	btn_f1_mcontour.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_mcontour.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_mhull;
	btn_f1_mhull.setSize( Vector2f( 160, 30 ) );
	btn_f1_mhull.setPosition( left_start + 160*1 , 521 );
	btn_f1_mhull.setOutlineThickness( 1 );
	btn_f1_mhull.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_mhull.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_mfingers;
	btn_f1_mfingers.setSize( Vector2f( 160, 30 ) );
	btn_f1_mfingers.setPosition( left_start + 160*2 , 521 );
	btn_f1_mfingers.setOutlineThickness( 1 );
	btn_f1_mfingers.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_mfingers.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f1_mpalm;
	btn_f1_mpalm.setSize( Vector2f( 160, 30 ) );
	btn_f1_mpalm.setPosition( left_start + 160*3 , 521 );
	btn_f1_mpalm.setOutlineThickness( 1 );
	btn_f1_mpalm.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f1_mpalm.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_f2_mcontour;
	btn_f2_mcontour.setSize( Vector2f( 160, 30 ) );
	btn_f2_mcontour.setPosition( left_start+650 + 160*0 , 521 );
	btn_f2_mcontour.setOutlineThickness( 1 );
	btn_f2_mcontour.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_mcontour.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_mhull;
	btn_f2_mhull.setSize( Vector2f( 160, 30 ) );
	btn_f2_mhull.setPosition( left_start+650 + 160*1 , 521 );
	btn_f2_mhull.setOutlineThickness( 1 );
	btn_f2_mhull.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_mhull.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_mfingers;
	btn_f2_mfingers.setSize( Vector2f( 160, 30 ) );
	btn_f2_mfingers.setPosition( left_start+650 + 160*2 , 521 );
	btn_f2_mfingers.setOutlineThickness( 1 );
	btn_f2_mfingers.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_mfingers.setFillColor( Color( 0, 0, 0, 255 ) );
	//RectangleShape btn_f2_mpalm;
	btn_f2_mpalm.setSize( Vector2f( 160, 30 ) );
	btn_f2_mpalm.setPosition( left_start+650 + 160*3 , 521 );
	btn_f2_mpalm.setOutlineThickness( 1 );
	btn_f2_mpalm.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_f2_mpalm.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_mode1;
	btn_mode1.setSize( Vector2f( 130, 30 ) );
	btn_mode1.setPosition( left_start + 130*0 , 561 );
	btn_mode1.setOutlineThickness( 1 );
	btn_mode1.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_mode1.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_mode2;
	btn_mode2.setSize( Vector2f( 130, 30 ) );
	btn_mode2.setPosition( left_start + 130*1 , 561 );
	btn_mode2.setOutlineThickness( 1 );
	btn_mode2.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_mode2.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_mode3;
	btn_mode3.setSize( Vector2f( 130, 30 ) );
	btn_mode3.setPosition( left_start + 130*2 , 561 );
	btn_mode3.setOutlineThickness( 1 );
	btn_mode3.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_mode3.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_mode4;
	btn_mode4.setSize( Vector2f( 130, 30 ) );
	btn_mode4.setPosition( left_start + 130*3 , 561 );
	btn_mode4.setOutlineThickness( 1 );
	btn_mode4.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_mode4.setFillColor( Color( 0, 0, 0, 255 ) );

	//RectangleShape btn_mode5;
	btn_mode5.setSize( Vector2f( 130, 30 ) );
	btn_mode5.setPosition( left_start + 130*4 , 561 );
	btn_mode5.setOutlineThickness( 1 );
	btn_mode5.setOutlineColor( Color( 0, 255, 0, 255 ) );
	btn_mode5.setFillColor( Color( 0, 0, 0, 255 ) );

	//Text txt_none;
	txt_none.setString( "None" );
	txt_none.setFont( this->fonts->trebuc );
	txt_none.setColor( Color( 0, 255, 0, 255 ) );
	txt_none.setCharacterSize( 17 );
	//Text txt_original;
	txt_original.setString( "Original" );
	txt_original.setFont( this->fonts->trebuc );
	txt_original.setColor( Color( 0, 255, 0, 255 ) );
	txt_original.setCharacterSize( 17 );
	//Text txt_grayscale;
	txt_grayscale.setString( "Grayscale" );
	txt_grayscale.setFont( this->fonts->trebuc );
	txt_grayscale.setColor( Color( 0, 255, 0, 255 ) );
	txt_grayscale.setCharacterSize( 17 );
	//Text txt_gaussed;
	txt_gaussed.setString( "Gaussed" );
	txt_gaussed.setFont( this->fonts->trebuc );
	txt_gaussed.setColor( Color( 0, 255, 0, 255 ) );
	txt_gaussed.setCharacterSize( 17 );
	//Text txt_thresholded;
	txt_thresholded.setString( "Thresholded" );
	txt_thresholded.setFont( this->fonts->trebuc );
	txt_thresholded.setColor( Color( 0, 255, 0, 255 ) );
	txt_thresholded.setCharacterSize( 17 );
	//Text txt_contour;
	txt_contour.setString( "Contour" );
	txt_contour.setFont( this->fonts->trebuc );
	txt_contour.setColor( Color( 0, 255, 0, 255 ) );
	txt_contour.setCharacterSize( 17 );
	//Text txt_hull;
	txt_hull.setString( "Hull" );
	txt_hull.setFont( this->fonts->trebuc );
	txt_hull.setColor( Color( 0, 255, 0, 255 ) );
	txt_hull.setCharacterSize( 17 );
	//Text txt_fingers;
	txt_fingers.setString( "Fingers" );
	txt_fingers.setFont( this->fonts->trebuc );
	txt_fingers.setColor( Color( 0, 255, 0, 255 ) );
	txt_fingers.setCharacterSize( 17 );
	//Text txt_palm;
	txt_palm.setString( "Palm" );
	txt_palm.setFont( this->fonts->trebuc );
	txt_palm.setColor( Color( 0, 255, 0, 255 ) );
	txt_palm.setCharacterSize( 17 );

	int y_bound = txt_none.getLocalBounds().height/2 + 5;

	//Text txt_f1_none;
	txt_f1_none = txt_none;
	txt_f1_none.setPosition( (btn_f1_fnone.getPosition().x + btn_f1_fnone.getSize().x/2 - txt_none.getLocalBounds().width/2 ), (btn_f1_fnone.getPosition().y + btn_f1_fnone.getSize().y/2 - y_bound ) );
	//Text txt_f1_original;
	txt_f1_original = txt_original;
	txt_f1_original.setPosition( (btn_f1_foriginal.getPosition().x + btn_f1_foriginal.getSize().x/2 - txt_original.getLocalBounds().width/2 ), (btn_f1_foriginal.getPosition().y + btn_f1_foriginal.getSize().y/2 - y_bound ) );
	////Text txt_f1_grayscale;
	txt_f1_grayscale = txt_grayscale;
	txt_f1_grayscale.setPosition( (btn_f1_fgrayscale.getPosition().x + btn_f1_fgrayscale.getSize().x/2 - txt_grayscale.getLocalBounds().width/2 ), (btn_f1_fgrayscale.getPosition().y + btn_f1_fgrayscale.getSize().y/2 - y_bound ) );
	////Text txt_f1_gaussed;
	txt_f1_gaussed = txt_gaussed;
	txt_f1_gaussed.setPosition( (btn_f1_fgaussed.getPosition().x + btn_f1_fgaussed.getSize().x/2 - txt_gaussed.getLocalBounds().width/2 ), (btn_f1_fgaussed.getPosition().y + btn_f1_fgaussed.getSize().y/2 - y_bound ) );
	////Text txt_f1_thresholded;
	txt_f1_thresholded = txt_thresholded;
	txt_f1_thresholded.setPosition( (btn_f1_fthresholded.getPosition().x + btn_f1_fthresholded.getSize().x/2 - txt_thresholded.getLocalBounds().width/2 ), (btn_f1_fthresholded.getPosition().y + btn_f1_fthresholded.getSize().y/2 - y_bound ) );
	////Text txt_f1_contour;
	txt_f1_contour = txt_contour;
	txt_f1_contour.setPosition( (btn_f1_mcontour.getPosition().x + btn_f1_mcontour.getSize().x/2 - txt_contour.getLocalBounds().width/2 ), (btn_f1_mcontour.getPosition().y + btn_f1_mcontour.getSize().y/2 - y_bound ) );
	////Text txt_f1_hull;
	txt_f1_hull = txt_hull;
	txt_f1_hull.setPosition( (btn_f1_mhull.getPosition().x + btn_f1_mhull.getSize().x/2 - txt_hull.getLocalBounds().width/2 ), (btn_f1_mhull.getPosition().y + btn_f1_mhull.getSize().y/2 - y_bound ) );
	////Text txt_f1_fingers;
	txt_f1_fingers = txt_fingers;
	txt_f1_fingers.setPosition( (btn_f1_mfingers.getPosition().x + btn_f1_mfingers.getSize().x/2 - txt_fingers.getLocalBounds().width/2 ), (btn_f1_mfingers.getPosition().y + btn_f1_mfingers.getSize().y/2 - y_bound ) );
	////Text txt_f1_palm;
	txt_f1_palm = txt_palm;
	txt_f1_palm.setPosition( (btn_f1_mpalm.getPosition().x + btn_f1_mpalm.getSize().x/2 - txt_palm.getLocalBounds().width/2 ), (btn_f1_mpalm.getPosition().y + btn_f1_mpalm.getSize().y/2 - y_bound ) );

	//Text txt_f2_none;
	txt_f2_none = txt_none;
	txt_f2_none.setPosition( (btn_f2_fnone.getPosition().x + btn_f2_fnone.getSize().x/2 - txt_none.getLocalBounds().width/2 ), (btn_f2_fnone.getPosition().y + btn_f2_fnone.getSize().y/2 - y_bound ) );
	//Text txt_f2_original;
	txt_f2_original = txt_original;
	txt_f2_original.setPosition( (btn_f2_foriginal.getPosition().x + btn_f2_foriginal.getSize().x/2 - txt_original.getLocalBounds().width/2 ), (btn_f2_foriginal.getPosition().y + btn_f2_foriginal.getSize().y/2 - y_bound ) );
	////Text txt_f2_grayscale;
	txt_f2_grayscale = txt_grayscale;
	txt_f2_grayscale.setPosition( (btn_f2_fgrayscale.getPosition().x + btn_f2_fgrayscale.getSize().x/2 - txt_grayscale.getLocalBounds().width/2 ), (btn_f2_fgrayscale.getPosition().y + btn_f2_fgrayscale.getSize().y/2 - y_bound ) );
	////Text txt_f2_gaussed;
	txt_f2_gaussed = txt_gaussed;
	txt_f2_gaussed.setPosition( (btn_f2_fgaussed.getPosition().x + btn_f2_fgaussed.getSize().x/2 - txt_gaussed.getLocalBounds().width/2 ), (btn_f2_fgaussed.getPosition().y + btn_f2_fgaussed.getSize().y/2 - y_bound ) );
	////Text txt_f2_thresholded;
	txt_f2_thresholded = txt_thresholded;
	txt_f2_thresholded.setPosition( (btn_f2_fthresholded.getPosition().x + btn_f2_fthresholded.getSize().x/2 - txt_thresholded.getLocalBounds().width/2 ), (btn_f2_fthresholded.getPosition().y + btn_f2_fthresholded.getSize().y/2 - y_bound ) );
	////Text txt_f2_contour;
	txt_f2_contour = txt_contour;
	txt_f2_contour.setPosition( (btn_f2_mcontour.getPosition().x + btn_f2_mcontour.getSize().x/2 - txt_contour.getLocalBounds().width/2 ), (btn_f2_mcontour.getPosition().y + btn_f2_mcontour.getSize().y/2 - y_bound ) );
	////Text txt_f2_hull;
	txt_f2_hull = txt_hull;
	txt_f2_hull.setPosition( (btn_f2_mhull.getPosition().x + btn_f2_mhull.getSize().x/2 - txt_hull.getLocalBounds().width/2 ), (btn_f2_mhull.getPosition().y + btn_f2_mhull.getSize().y/2 - y_bound ) );
	////Text txt_f2_fingers;
	txt_f2_fingers = txt_fingers;
	txt_f2_fingers.setPosition( (btn_f2_mfingers.getPosition().x + btn_f2_mfingers.getSize().x/2 - txt_fingers.getLocalBounds().width/2 ), (btn_f2_mfingers.getPosition().y + btn_f2_mfingers.getSize().y/2 - y_bound ) );
	////Text txt_f2_palm;
	txt_f2_palm = txt_palm;
	txt_f2_palm.setPosition( (btn_f2_mpalm.getPosition().x + btn_f2_mpalm.getSize().x/2 - txt_palm.getLocalBounds().width/2 ), (btn_f2_mpalm.getPosition().y + btn_f2_mpalm.getSize().y/2 - y_bound ) );

	//Text txt_mode1;
	txt_mode1.setString( "1-Finger" );
	txt_mode1.setFont( this->fonts->trebuc );
	txt_mode1.setColor( Color( 0, 255, 0, 255 ) );
	txt_mode1.setCharacterSize( 17 );
	txt_mode1.setPosition( (btn_mode1.getPosition().x + btn_mode1.getSize().x/2 - txt_mode1.getLocalBounds().width/2 ), (btn_mode1.getPosition().y + btn_mode1.getSize().y/2 - y_bound ) );
	//Text txt_mode2;
	txt_mode2.setString( "2-Finger" );
	txt_mode2.setFont( this->fonts->trebuc );
	txt_mode2.setColor( Color( 0, 255, 0, 255 ) );
	txt_mode2.setCharacterSize( 17 );
	txt_mode2.setPosition( (btn_mode2.getPosition().x + btn_mode2.getSize().x/2 - txt_mode2.getLocalBounds().width/2 ), (btn_mode2.getPosition().y + btn_mode2.getSize().y/2 - y_bound ) );
	//Text txt_mode3;
	txt_mode3.setString( "3-Finger" );
	txt_mode3.setFont( this->fonts->trebuc );
	txt_mode3.setColor( Color( 0, 255, 0, 255 ) );
	txt_mode3.setCharacterSize( 17 );
	txt_mode3.setPosition( (btn_mode3.getPosition().x + btn_mode3.getSize().x/2 - txt_mode3.getLocalBounds().width/2 ), (btn_mode3.getPosition().y + btn_mode3.getSize().y/2 - y_bound ) );
	//Text txt_mode4;
	txt_mode4.setString( "4-Finger" );
	txt_mode4.setFont( this->fonts->trebuc );
	txt_mode4.setColor( Color( 0, 255, 0, 255 ) );
	txt_mode4.setCharacterSize( 17 );
	txt_mode4.setPosition( (btn_mode4.getPosition().x + btn_mode4.getSize().x/2 - txt_mode4.getLocalBounds().width/2 ), (btn_mode4.getPosition().y + btn_mode4.getSize().y/2 - y_bound ) );
	//Text txt_mode5;
	txt_mode5.setString( "5-Finger" );
	txt_mode5.setFont( this->fonts->trebuc );
	txt_mode5.setColor( Color( 0, 255, 0, 255 ) );
	txt_mode5.setCharacterSize( 17 );
	txt_mode5.setPosition( (btn_mode5.getPosition().x + btn_mode5.getSize().x/2 - txt_mode5.getLocalBounds().width/2 ), (btn_mode5.getPosition().y + btn_mode5.getSize().y/2 - y_bound ) );

	//Text txt_information;
	txt_information.setString( "xxx" );
	txt_information.setFont( this->fonts->trebuc );
	txt_information.setColor( Color( 0, 255, 0, 255 ) );
	txt_information.setCharacterSize( 17 );
	txt_information.setPosition( left_start, 620 );
}

bool GuiElements::IsBounding( Vector2< int > p, RectangleShape& r )
{
	FloatRect b = r.getGlobalBounds();
	return ( p.x > b.left ) && ( p.x < b.width+b.left ) && ( p.y > b.top ) && ( p.y < b.top+b.height );
}

void GuiElements::MakeInfoText( double fps, bool hand_found )
{
	string str = "Frame / Second: " + to_string( int(fps) ) + "\nA Possible Hand Found: ";
	if( hand_found )
	{
		str += "TRUE";
	}
	else
	{
		str += "FALSE";
	}
	this->txt_information.setString( str );
}