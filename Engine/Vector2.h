#pragma once
class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();

	float cross(const Vector2& other) const;

	float x, y;
};

