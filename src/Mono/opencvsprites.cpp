#include "opencvsprites.hpp"

using namespace cv;
using namespace sf;
using namespace std;

OpencvSprites::OpencvSprites( )
{
	for( int i=0; i<2; ++i )
	{
		Uint8* pixelarr = new Uint8[ S_WIDTH * S_HEIGHT * 4 ];
		this->pixels.push_back( pixelarr );
		this->texture.push_back( Texture() );
		this->texture[i].create( S_WIDTH, S_HEIGHT );
		this->sprite.push_back( Sprite( this->texture[i] ) );
	}
}

void OpencvSprites::Set( int sprite_index, Mat& mat, int color_enum )
{
	Mat mat_rgba( S_WIDTH, S_HEIGHT, CV_8UC4, this->pixels[ sprite_index ] );
	cvtColor( mat, mat_rgba, color_enum );
	this->texture[ sprite_index ].update( mat_rgba.data );
	this->sprite[ sprite_index ].setTexture( this->texture[ sprite_index ] );
}

OpencvSprites::~OpencvSprites( )
{
	for( int i=0; i<2; ++i )
	{
		delete this->pixels[i];
	}
}