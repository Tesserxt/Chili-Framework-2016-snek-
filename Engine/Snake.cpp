#include "Snake.h"
#include "assert.h"


Snake::Snake(Board& brd)
{
	bodyColors[0] = { 10, 100, 32 };
	bodyColors[1] = { 10, 130, 48 };
	bodyColors[2] = { 18, 160, 48 };
	bodyColors[3] = { 10, 130, 48 };

	for (int i = 0; i < nSegmentsMax; ++i)
	{
		segment[i] = brd.in_loc;
	}
}

void Snake::follow_segment()
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segment[i] = segment[i-1];
	}
}

void Snake::moveby(location delta_loc)
{
	follow_segment();
	segment[0].add(delta_loc);
}

void Snake::DrawSegment( Board& brd )
{	
	for (int i = 1; i < nSegments; i++)
	{
		brd.DrawCell(segment[i], bodyColors[i%4]);
	}
	brd.DrawCell(segment[0], Colors::Yellow);
}

void Snake::grow()
{
	if (nSegments < nSegmentsMax)
	{
		nSegments++;
	}
}

void Snake::speed( int& snekMotionRate)
{
	int currentPortion = nSegments / 3;
	if ( currentPortion > previousPortion  && snekMotionRate > 5 )
	{
		previousPortion = currentPortion;
		snekMotionRate -= 1; //increasing speed	
	}
}

bool Snake::isColliding( location& target)
{
	for (int i = 0; i < nSegments; i++)
	{
		if ( segment[i] == target )
		{
			return true;
		}
		
	}
	return false;	
}

bool Snake::isCollidingToItself(location& target)
{
	for (int i = 1; i < nSegments - 1; i++)
	{
		if (segment[i] == target)
		{
			return true;
		}

	}
	return false;
}

location Snake::getNextHeadLoc(location& delta_loc)
{
	location copy_loc( segment[0] );
	copy_loc.add(delta_loc);
	return copy_loc;
}

