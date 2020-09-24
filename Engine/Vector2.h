#pragma once

class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();

	float Cross(const Vector2& other) const;
	float Angle() const;
	float Length() const;

	Vector2& operator=(const Vector2& other);
	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator*=(const float f);

	static Vector2 fromPolar(float length, float angle);

	float x, y;
};

