#ifndef __TIMECTRL__
#define __TIMECTRL__

#include <SFML\System.hpp>

using namespace sf;
using namespace std;

class TimeControl
{
public:
	Clock clock;
	double t_total;
	double t_loop;
	double t_last_fps_update;
	double fps;
	TimeControl();
	void Run();
};

#endif