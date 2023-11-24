#pragma once

#include "AcrossTheGame.h"
#include "RectF.h"
#include "Graphics.h"
#include "Beveler.h"

class Walls
{
public:
	Walls(const RectF& in_innerbounds, int in_thickness, Color baseColor);
	void Draw(Graphics& gfx) ;
	const RectF& GetInnerBounds() const;

private:
	RectF innerbounds;
	int thickness;
	Beveler bevel;
};
