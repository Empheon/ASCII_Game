#pragma once
#include <algorithm>

class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();
	float Angle();
	float Normalize();
	float x, y;
};

