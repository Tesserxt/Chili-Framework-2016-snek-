#include "Board.h"
#include "assert.h"
#include <cmath>
#include "snake.h"
#include "Goal.h"

Board::Board(Graphics& gfex)
	:
	gfx(gfex),
	in_loc{ 10,10 },
	walls(RectF(4, 28, 2, 25), 8, { 125, 0, 128 })
{
	hasObstacle.resize(walls.GetInnerBounds().right * walls.GetInnerBounds().bottom, false);
}

void Board::DrawCell(location loc, Color c)
{
	gfx.DrawRectDim(loc.x * space, loc.y * space, dim, dim, c);
}

void Board::DrawWalls()
{
	walls.Draw(gfx);
}

bool Board::IsInsideBoard( location& loc )
{
	return  loc.x >= walls.GetInnerBounds().left && loc.x < walls.GetInnerBounds().right &&
		    loc.y >= walls.GetInnerBounds().top &&  loc.y < walls.GetInnerBounds().bottom ;
}

bool Board::CheckForObstacles(const location& loc) const
{
	return hasObstacle[ loc.y * walls.GetInnerBounds().right + loc.x ];
}

void Board::SpawnObstacles(Snake& snek, class Goal& goal, std::mt19937& rng)
{
	std::uniform_int_distribution<int> xDist(walls.GetInnerBounds().left,walls.GetInnerBounds().right - 1);
	std::uniform_int_distribution<int> yDist(walls.GetInnerBounds().top, walls.GetInnerBounds().bottom - 1);
	location new_loc;
	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);

	} while (snek.isColliding(new_loc) && CheckForObstacles(new_loc) && goal.getLoc() == new_loc );
	
	hasObstacle[new_loc.y * walls.GetInnerBounds().right + new_loc.x] = { true };

}

void Board::DrawObstacles()
{
	for (int i = walls.GetInnerBounds().left; i < walls.GetInnerBounds().right; i++)
	{
		for (int j = walls.GetInnerBounds().top; j < walls.GetInnerBounds().bottom; j++)
		{
			if(CheckForObstacles( {i,j} ))
				DrawCell( {i, j}, Colors::Gray);
		}
	}
}
