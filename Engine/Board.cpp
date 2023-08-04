#include "Board.h"
#include "assert.h"

Board::Board(Graphics& gfex)
	:
	gfx(gfex)
{
	in_loc = { x1 , y1 };
}

void Board::DrawCell(location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.y >= 0);
	assert(loc.x < width);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * space, loc.y * space, dim, dim, c);
}

void Board::Boundary()
{
	for (int i = x1 * space; i < width * space; i++)
	{
		gfx.PutPixel( i, y1 * space - 3, Colors::White);
		gfx.PutPixel( i, y1 * space - 2, Colors::White ); //Top

		gfx.PutPixel( i, height * space - 3, Colors::White);
		gfx.PutPixel( i, height * space - 2, Colors::White ); //Bottom
	}
	for (int i = y1 * space; i < height * space; i++)
	{
		gfx.PutPixel( x1 * space - 3, i, Colors::White);
		gfx.PutPixel( x1 * space - 2, i, Colors::White); //Left

		gfx.PutPixel( width * space - 3, i, Colors::White);
		gfx.PutPixel( width * space - 2, i, Colors::White); //Right
	}
}

int Board::getx1()
{
	return x1;
}

int Board::gety1()
{
	return y1;
}

int Board::GetGridHeight()
{
    return height;
}

int Board::GetGridWidth()
{
    return width;
}

bool Board::IsInsideBoard( location& loc )
{
	return  loc.x >= x1 && loc.x < width  &&
			loc.y >= y1 && loc.y < height;
}

void Board::obstacle()
{
}
