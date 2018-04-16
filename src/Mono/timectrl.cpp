#include "timectrl.hpp"

TimeControl::TimeControl()
{
	this->clock.restart();
	this->t_total = 0;
	this->t_loop = 0;
	this->t_last_fps_update = 0;
	this->fps = 1;
}

void TimeControl::Run()
{
	double elap = this->clock.getElapsedTime().asMicroseconds();
	this->t_loop = elap - this->t_total;
	this->t_total = elap;

	//update fps 5 times in every second, not every frame
	if( elap - this->t_last_fps_update > 200000 )
	{
		this->fps = 1000000 / this->t_loop;
		this->t_last_fps_update = elap;
	}
}