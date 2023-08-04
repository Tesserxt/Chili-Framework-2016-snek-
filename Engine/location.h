#pragma once

struct location
{
	void add(location& delta_loc)
	{
		x += delta_loc.x;
		y += delta_loc.y;

	}
	bool operator==(location& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};
