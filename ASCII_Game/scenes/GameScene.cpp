#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete wall;
	delete wall1;
	delete wall2;
	delete wall3;
	delete wall4;
}

void GameScene::OnUpdate() {
}

void GameScene::OnLoad() {

	playerCount = parent->input.GetConnectedGamepadCount();

	for (int i = 0; i < playerCount; ++i) {
		Gamepad* gp = parent->input.GetGamepad(i);
		tanks.push_back(Tank(playerColors[i], gp, i * 8));
	}

	wall = new Wall(6, 7, 30, 15);
	wall1 = new Wall(85, 0, 15, 80);
	wall2 = new Wall(40, 60, 45, 4);
	wall3 = new Wall(63, 20, 5, 20);
	wall4 = new Wall(8, 35, 27, 34);

	Instantiate(wall);
	Instantiate(wall1);
	Instantiate(wall2);
	Instantiate(wall3);
	Instantiate(wall4);

	for (auto& t : tanks) {
		Instantiate(&t);
	}
}

void GameScene::OnPreDraw(Renderer* renderer) {
	renderer->Clear(' ', 0x07);
}

void GameScene::DestroyTank(Tank* tank) {
	destroyedTanks.push_back(tank);

	if (destroyedTanks.size() == playerCount - 1) {
		parent->LoadScene(new GameScene());
	}
}
