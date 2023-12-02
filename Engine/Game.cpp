/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek(brd),
	rng(std::random_device()()),
	goal(brd, snek, rng)
{	
	delta_loc = { 0, 0 };	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (GameIsStarted)
	{
		if (!GameIsOver)
		{
			if ( wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x != -1 )
			{
				delta_loc = { 1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x != 1)
			{
				delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y != 1 )
			{
				delta_loc = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y != -1 )
			{
				delta_loc = { 0, 1 };
			}

			snekMotionCounter++;
			if (snekMotionCounter >= snekMotionRate)
			{
				
				snekMotionCounter = 0;
				location NextHeadLoc = snek.getNextHeadLoc(delta_loc);
				if (wnd.kbd.KeyIsPressed(VK_SPACE))
				{
					snek.grow();
					snek.speed(snekMotionRate);
				}
				if (brd.CheckForObstacles(NextHeadLoc))
				{
					snekMotionRate -= 1; // increasing snek speed when eaten obstacle
					brd.ResetObstacle(NextHeadLoc); // "Resetting obst to false to visually remove it from the board."
					brd.maxObstacles -= 1; // "Reducing `maxObstacles` to ensure they are logically removed from the board."
				}
				if ( !brd.IsInsideBoard(NextHeadLoc) || snek.isCollidingToItself(NextHeadLoc) )
				{
					GameIsOver = true;
				}
				else
				{
					const bool eating = (NextHeadLoc == goal.getLoc());
					if (eating && snekMotionRate > 5)
					{
						snek.grow();
						//snek.speed(snekMotionRate);
						
					}
					snek.moveby(delta_loc);

					if (eating)
					{
						goal.Respawn(brd, snek, rng);
			
					}
				}
			}
			/*snekMoveCounter++;
			if (snekMoveCounter >= snekMoveSpeed && snekMotionRate > 5)
			{
				--snekMotionRate;
				snekMoveCounter = 0;
			}*/
		}
	}
	else
	{
		GameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}


void Game::ComposeFrame()
{
	std::uniform_int_distribution<int> dist(0,255);
	Color c(dist(rng), dist(rng), dist(rng));
	
	if (GameIsStarted)
	{
		{
			brd.SpawnObstacles(snek, goal, rng);
		}
		brd.DrawObstacles();
		snek.DrawSegment(brd);
		goal.Draw(brd);
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver(250, 250, gfx);
		}
		brd.DrawWalls();
	}
	else
	{
		SpriteCodex::DrawTitle( 280, 200, gfx );
	}


}
