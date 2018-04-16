#include "fonts.hpp"

using namespace sf;
using namespace std;

FontControl::FontControl()
{
	if( !this->trebuc.loadFromFile( "C:/Windows/Fonts/trebuc.ttf" ) )
		exit( 1 );
}