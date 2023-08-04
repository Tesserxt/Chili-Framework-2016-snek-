#pragma once
#include "Graphics.h"
#include "location.h"
#include "Board.h"
#include <random>

class Snake
{
public:
	Snake(Board& brd);
	void follow_segment();
	void moveby(          location delta_loc);
	void DrawSegment(     Board& brd );
	void grow();
	void speed( int& snekMotionRate );
	bool isColliding(         location& target );
	bool isCollidingToItself( location& target );
	location getNextHeadLoc(  location& delta_loc);

	
	static int constexpr nSegmentsMax = 100;
	location segment[nSegmentsMax];
	int nSegments = 1;
	int offset = 3;

	static constexpr int nBodyColors = 4;
	Color bodyColors[nBodyColors];
	int previousPortion = 0;
};