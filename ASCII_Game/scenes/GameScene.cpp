#include "GameScene.h"
#include "ScoreScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::OnUpdate() {
}

void GameScene::OnLoad() {

	levels = {
		level1()
	};

	LevelInfo* currentLevel = &levels[0];

	for (WallInfo& wi : currentLevel->walls) {
		Instantiate(&wi.wall, wi.position);
	}

	playerCount = parent->input.GetConnectedGamepadCount();

	for (int i = 0; i < playerCount; ++i) {
		Gamepad* gp = parent->input.GetGamepad(i);
		tanks.push_back(Tank(playerColors[i], gp));
	}

	int i = 0;
	for (auto& t : tanks) {
		Instantiate(&t, currentLevel->spawns[i++]);
	}
}

void GameScene::OnPreDraw(Renderer* renderer) {
	renderer->Clear(' ', 0x07);
}

void GameScene::DestroyTank(Tank* tank) {
	destroyedTanks.push(tank);

	if (tanks.size() == 1) {
		parent->LoadScene(new ScoreScene(destroyedTanks));
		return;
	}

	if (destroyedTanks.size() == playerCount - 1) {
		Tank* winner;
		for (auto& t : tanks) {
			if (t.IsValidInstance()) {
				winner = &t;
				break;
			}
		}
		destroyedTanks.push(winner);

		parent->LoadScene(new ScoreScene(destroyedTanks));
	}
}
