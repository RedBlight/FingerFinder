#include "main.hpp"

using namespace std;

int main()
{
	TimeControl timer;
	FontControl fonts;
	SfmlWindowControl window;
	OpencvSprites sprites;
	CameraControl camera_1( 0 );
	CameraControl camera_2( 1 );
	VisionControl vision( &camera_1, &camera_2 );
	GuiElements guielem( &fonts, window.vm.width, window.vm.height );
	DisplayControl display( &window, &timer, &fonts, &sprites, &guielem );
	GuiControl guicon( &guielem, &window );

	sprites.sprite[0].setPosition( ( window.vm.width / 2 ) - 645 , 1 );
	sprites.sprite[1].setPosition( ( window.vm.width / 2 ) + 5 , 1 );


	while( guicon.running )
	{
		timer.Run();
		guicon.Run();
		vision.Run( guicon.mode_finger );
		sprites.Set( 0, vision.GetMat( 1, guicon.mode_feed1, guicon.f1_contour, guicon.f1_hull, guicon.f1_fingers, guicon.f1_palm ), COLOR_BGR2RGBA );
		sprites.Set( 1, vision.GetMat( 2, guicon.mode_feed2, guicon.f2_contour, guicon.f2_hull, guicon.f2_fingers, guicon.f2_palm ), COLOR_BGR2RGBA );
		guielem.MakeInfoText( timer.fps, vision.hand_found );
		display.Run();
	}

	return 0;
}