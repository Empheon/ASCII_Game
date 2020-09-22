#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete wall;
}

void GameScene::OnUpdate() {
}

void GameScene::OnLoad() {

	int playerCount = parent->input.GetConnectedGamepadCount();

	for (int i = 0; i < playerCount; ++i) {
		Gamepad* gp = parent->input.GetGamepad(i);
		tanks.push_back(Tank(playerColors[i], gp));
	}

	wall = new Wall(6, 12, 30, 6);

	for (auto& t : tanks) {
		Instantiate(&t);
	}

	Instantiate(wall);
}

void GameScene::OnPreDraw(Renderer* renderer) {
	renderer->Clear(' ', 0x07);
}