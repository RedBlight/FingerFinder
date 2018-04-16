#include "sfmlwindow.hpp"

using namespace sf;
using namespace std;

SfmlWindowControl::SfmlWindowControl()
{
	this->vm = VideoMode::getDesktopMode();

	// to set them all maximum by default
	this->cs.depthBits = 999;
	this->cs.stencilBits = 99;
	this->cs.antialiasingLevel = 99;
	this->cs.majorVersion = 99;
	this->cs.minorVersion = 99;

	this->window = new RenderWindow( this->vm, "Fingerfinder", Style::Fullscreen, this->cs );
    this->window->setVerticalSyncEnabled(false);

	// get back default maximum values;
	this->cs = this->window->getSettings();
	
	this->window->setActive();
}

SfmlWindowControl::~SfmlWindowControl()
{
	delete this->window;
}
