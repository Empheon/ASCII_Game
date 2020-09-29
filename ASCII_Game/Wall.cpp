#include "Wall.h"

void Wall::OnInit() {
	depth = 10;
	SetStatic();
}

void Wall::OnDraw(Renderer* renderer) {
	
	renderer->DrawChar(position.x, position.y, WALL_TOP_LEFT, 0x0f, depth);
	renderer->DrawChar(position.x + width - 1, position.y, WALL_TOP_RIGHT, 0x0f, depth);
	renderer->DrawChar(position.x, position.y + height - 1, WALL_BOTTOM_LEFT, 0x0f, depth);
	renderer->DrawChar(position.x + width - 1, position.y + height - 1, WALL_BOTTOM_RIGHT, 0x0f, depth);

	if (width > 2) {
		renderer->DrawRect(position.x + 1, position.y, width - 2, 1, WALL_HOR, 0x0f, depth);
		renderer->DrawRect(position.x + 1, position.y + height - 1, width - 2, 1, WALL_BOTTOM, 0x0f, depth);
	}

	if (height > 2) {
		renderer->DrawRect(position.x, position.y + 1, 1, height - 2, WALL_VER, 0x0f, depth);
		renderer->DrawRect(position.x + width - 1, position.y + 1, 1, height - 2, WALL_VER, 0x0f, depth);
	}

	if (width > 2 && height > 2) {
		renderer->DrawRect(position.x + 1, position.y + 1, width - 2, height - 2, L' ', 0x0f, depth);
	}
	//renderer->DrawRect(position.x, position.y, width, height, WALL_TOP_LEFT, 0x0f);
}