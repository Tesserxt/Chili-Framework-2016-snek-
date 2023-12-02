#pragma once

#include <iostream>
#include <vector>
#include "AcrossTheGame.h"
#include "Graphics.h"
#include "location.h"
#include "RectF.h"
#include "Vec2.h"
#include "Walls.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfex);
	void DrawCell(location loc, Color c);
	void DrawWalls();
	bool IsInsideBoard(location& loc);
	bool CheckForObstacles(const location& loc) const;
	void SpawnObstacles(class Snake& snek, class Goal& goal, std::mt19937& rng);
	void DrawObstacles();
	void ResetObstacle(location& loc);
	location in_loc;
	Graphics& gfx;
	Walls walls;
	int maxObstacles = 50; // max number of obstacles allowed to spawn
	int obstSpawned = 0;    // number of obstacles spawned


private:
	static constexpr int cellpadding = 2;
	static constexpr int dim = DIM;

	std::vector<bool> hasObstacle;
	
//bool hasObstacle[28 * 25] = { false };
};
