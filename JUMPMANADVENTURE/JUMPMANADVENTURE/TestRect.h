#pragma once
#include "Vec2.h"

class TestRect
{
public:
	float top;
	float bottom;
	float left;
	float right;

public:
	//
	TestRect() :
		top(0),
		bottom(0),
		left(0),
		right(0)
	{
	}
	float getWidth() const { return right - left; }
	float getHeight() const { return bottom - top; }

	//
	Vec2 getCenter();

	//
	bool isCol(const TestRect& testRect);

	void set_TL_Size(Vec2 posTL, Vec2 size);
};

