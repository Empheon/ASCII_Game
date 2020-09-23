#include "Vector2.h"

Vector2::Vector2(float x, float y)
	: x(x), y(y) {
}

Vector2::Vector2()
	: x(0.0f), y(0.0f) {
}

float Vector2::cross(const Vector2& other) const {
	return x * other.y + y * other.x;
}