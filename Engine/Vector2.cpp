#include "Vector2.h"

#include <cmath>

Vector2::Vector2(float x, float y)
    : x(x), y(y) {
}

Vector2::Vector2()
    : x(0.0f), y(0.0f) {
}

float Vector2::Angle() const{
    return atan2(y, x);
}

float Vector2::Length() const {
    return sqrtf(x * x + y * y);
}

float Vector2::Cross(const Vector2& other) const {
	return x * other.y + y * other.x;
}

Vector2& Vector2::operator=(const Vector2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) {
    return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator*=(const float f)
{
    x *= f;
    y *= f;
    return *this;
}

Vector2 Vector2::fromPolar(float length, float angle)
{
    return { length * cos(angle), length * sin(angle) };
}