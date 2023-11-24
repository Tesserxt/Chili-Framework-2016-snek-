#include "RectF.h"

RectF::RectF( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

RectF::RectF( const Vec2& topLeft,const Vec2 & bottomRight )
	:
	RectF( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

RectF::RectF( const Vec2& topLeft,int width,int height )
	:
	RectF( topLeft,topLeft + Vec2( width,height ) )
{
}

bool RectF::IsOverlappingWith( const RectF& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectF::IsContainedBy(const RectF& other)
{
	return right >= other.left && left <= other.right
		&& bottom >= other.top && top <= other.bottom;
}

RectF RectF::FromCenter(const Vec2& center, int halfwidth, int halfheight)
{
	Vec2 half(halfwidth, halfheight);
	return RectF( center - half, center + half );
}

RectF RectF::GetExpanded(int offset) const
{
	return RectF( left - offset, right + offset, top - offset, bottom + offset );
}

Vec2 RectF::GetCenter()
{
	return Vec2((right + left) / 2.0f, (top + bottom) / 2.0f);
}

RectF RectF::operator/(int rhs)
{
	return RectF(left / rhs, right / rhs, top / rhs, bottom / rhs);
}

RectF RectF::operator*(int rhs)
{
	return RectF(left * rhs, right * rhs, top * rhs, bottom * rhs);
}
