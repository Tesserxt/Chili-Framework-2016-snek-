#include "Goal.h"

Goal::Goal(Board& brd, Snake& snek, std::mt19937& rng)
{
	Respawn(brd, snek, rng);
}

void Goal::Respawn( Board& brd, Snake& snek, std::mt19937& rng)
{
	std::uniform_int_distribution<int> xDist(brd.walls.GetInnerBounds().left,  brd.walls.GetInnerBounds().right - 1);
	std::uniform_int_distribution<int> yDist(brd.walls.GetInnerBounds().top,   brd.walls.GetInnerBounds().bottom - 1);
	location new_loc;						   
	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);

	}while (snek.isColliding(new_loc));
	loc = new_loc;
	//Draw( brd );
}

void Goal::Draw( Board& brd )
{  
	brd.DrawCell(loc, c);
}

location Goal::getLoc()
{
	return loc;
}
