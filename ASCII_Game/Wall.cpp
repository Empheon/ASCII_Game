#include "Wall.h"

void Wall::OnDraw(Renderer* renderer) {
	renderer->DrawRect(x, y, width, height, '#', 0xfe);
}