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
	hasObstacle.resize( (walls.GetInnerBounds().right + 1 )* (walls.GetInnerBounds().bottom + 1), false); //incrementing height and width by + 1 for nextHeadLocation
}

void Board::DrawCell(location loc, Color c)
{
	gfx.DrawRectDim(loc.x * dim + cellpadding, loc.y * dim + cellpadding, dim - cellpadding * 2, dim - cellpadding * 2, c);
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
	obstSpawned = 0;
	for (int y = walls.GetInnerBounds().top; y < walls.GetInnerBounds().bottom; y++)
	{
		for (int x = walls.GetInnerBounds().left; x < walls.GetInnerBounds().right; x++)
		{
			if (CheckForObstacles({ x,y }))
			{
				obstSpawned++;
				if (obstSpawned > maxObstacles) // max 549
				{
					return;
				}
			}
		}
	}
	std::uniform_int_distribution<int> xDist(walls.GetInnerBounds().left,walls.GetInnerBounds().right - 1 );
	std::uniform_int_distribution<int> yDist(walls.GetInnerBounds().top, walls.GetInnerBounds().bottom - 1);
	location new_loc;
	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);

	} while(snek.isColliding(new_loc) || CheckForObstacles(new_loc) || goal.getLoc() == new_loc  );
	
	if( obstSpawned < maxObstacles )
		hasObstacle[new_loc.y * walls.GetInnerBounds().right + new_loc.x] = { true };
}

void Board::DrawObstacles()
{
	for (int y = walls.GetInnerBounds().top; y < walls.GetInnerBounds().bottom;y++)
	{
		for (int x = walls.GetInnerBounds().left; x < walls.GetInnerBounds().right; x++)
		{
			if (CheckForObstacles({ x,y }))
			{
				DrawCell({ x,y }, Colors::Magenta);
				//gfx.DrawRectDim(x * dim, y * dim, dim, dim, Colors::Gray);
				//i++;
			}
		}
	}
}

void Board::ResetObstacle(location& loc)
{
	hasObstacle[loc.y * walls.GetInnerBounds().right + loc.x] = false;
}
