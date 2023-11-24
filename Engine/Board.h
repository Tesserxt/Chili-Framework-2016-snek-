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
	location in_loc;
	Graphics& gfx;
	Walls walls;


private:
	static constexpr int space = SPACE;
	static constexpr int dim = DIM;
	std::vector<bool> hasObstacle;
//bool hasObstacle[28 * 25] = { false };
};
