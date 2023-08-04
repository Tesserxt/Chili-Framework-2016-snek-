#pragma once

#include "Board.h"
#include "location.h"
#include "Snake.h"
#include <random>

class Goal
{
public:
	Goal( Board& brd, Snake& snek, std::mt19937& rng );
	void Respawn( Board& brd, Snake& snek, std::mt19937& rng);
	void Draw( Board& brd );
	location getLoc();

private:
	location loc;
	Color c = Colors::Red;
};
