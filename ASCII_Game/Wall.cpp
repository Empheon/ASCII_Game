#include "Wall.h"

void Wall::OnDraw(Renderer* renderer) {
	renderer->DrawRect(position.x, position.y, width, height, '#', 0xfe);
}