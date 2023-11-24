#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF( int left_in,int right_in,int top_in,int bottom_in );
	RectF( const Vec2& topLeft,const Vec2& bottomRight );
	RectF( const Vec2& topLeft,int width,int height );
	bool IsOverlappingWith( const RectF& other ) const;
	bool IsContainedBy( const RectF& other);
	static RectF FromCenter(const Vec2& centre, int halfwidth, int halfheight);
	RectF GetExpanded(int offset) const;
	Vec2 GetCenter();
	RectF operator/(int rhs);
	RectF operator*(int rhs);
public:
	int left;
	int right;
	int top;
	int bottom;
};