#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::OnLoad() {
	int playerCount = parent->input.GetConnectedGamepadCount();

	for (int i = 0; i < playerCount; ++i) {
		Gamepad* gp = parent->input.GetGamepad(i);
		tanks.push_back(Tank(playerColors[i], gp));
	}

	for (auto& t : tanks) {
		Instantiate(&t);
	}
}

void GameScene::OnPreDraw() {
	parent->renderer->DrawRect(0, 0, parent->width, parent->height, '.', 0x07);
}