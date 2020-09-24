#include "GameScene.h"
#include "ScoreScene.h"

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

	wall = new Wall(30, 15);
	wall1 = new Wall(15, 80);
	wall2 = new Wall(45, 4);
	wall3 = new Wall(5, 20);
	wall4 = new Wall(27, 34);

	Instantiate(wall, {6, 7});
	Instantiate(wall1, {85, 0});
	Instantiate(wall2, {40, 60});
	Instantiate(wall3, {63, 20});
	Instantiate(wall4, {8, 35});

	for (auto& t : tanks) {
		Instantiate(&t);
	}
}

void GameScene::OnPreDraw(Renderer* renderer) {
	renderer->Clear(' ', 0x07);
}

void GameScene::DestroyTank(Tank* tank) {
	destroyedTanks.push(tank);

	if (destroyedTanks.size() == playerCount - 1) {

		Tank* winner;
		for (auto& t : tanks) {
			if (t.destroyed == false) {
				winner = &t;
				break;
			}
		}
		destroyedTanks.push(winner);

		parent->LoadScene(new ScoreScene(destroyedTanks));
	}
}
