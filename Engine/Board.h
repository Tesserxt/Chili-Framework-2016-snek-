#pragma once
#include "Graphics.h"
#include "location.h"

class Board
{
public:
	Board(Graphics& gfex);
	void DrawCell(location& loc, Color c);
	void Boundary();
	int getx1();
	int gety1();
	int  GetGridHeight();
	int  GetGridWidth();
	bool IsInsideBoard( location& loc );
	void obstacle();
	location in_loc;
	Graphics& gfx;

private:
	static constexpr int x1     =  3;
	static constexpr int y1     =  2;
	static constexpr int height =  28;
	static constexpr int width  =  36;
	static constexpr int space  =  20;

	static constexpr int dim    = 15;
	
};
