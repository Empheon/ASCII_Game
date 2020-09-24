#pragma once
#include <algorithm>

class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();

	float Cross(const Vector2& other) const;
	float Angle() const;
	float Length() const;
	float x, y;

	Vector2 operator+(const Vector2& other);
};

