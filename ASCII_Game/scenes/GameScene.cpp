#include "GameScene.h"
#include "ScoreScene.h"

GameScene::GameScene() {
	levels = {
		level1(),
		level2(),
		level3()
	};
}

GameScene::~GameScene() {
}

void GameScene::OnUpdate() {
	if (delayBeforeEnd > -1) {
		delayBeforeEnd--;
		if (delayBeforeEnd == 0) {
			EndGame();
		}
	}
}

void GameScene::OnLoad() {
	int randomLevelIndex;
	do {
		randomLevelIndex = (int)(((double)rand() / RAND_MAX) * levels.size());
	} while (randomLevelIndex == prevLevelIndex && levels.size() > 1);
	prevLevelIndex = randomLevelIndex;

	LevelInfo* currentLevel = &levels[randomLevelIndex];

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

	Instantiate(new Countdown());
}

void GameScene::OnPreDraw(Renderer* renderer) {
	renderer->Clear(' ', 0x07);
}

void GameScene::DestroyTank(Tank* tank) {
	destroyedTanks.push(tank);

	if (tanks.size() == 1) {
		delayBeforeEnd = (int)(DELAY_BEFORE_END * parent->targetFPS);
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

		delayBeforeEnd = (int) (DELAY_BEFORE_END * parent->targetFPS);
	}
}


void GameScene::StartGame() {
	for (Tank& t : tanks) {
		t.AllowAttack();
	}
}

void GameScene::EndGame() {
	parent->particles.Clear();
	parent->LoadScene(new ScoreScene(destroyedTanks));
}
