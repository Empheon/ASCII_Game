#pragma once

#include <scene/Scene.h>
#include <input/Gamepad.h>

#include <vector>
#include <stack>
#include "../Tank.h"
#include "../Wall.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	int playerCount;


	static constexpr WORD playerColors[] = { 0x0c, 0x0b, 0x0a, 0x0d };
	std::vector<Tank> tanks;
	std::stack<Tank*> destroyedTanks;
	Wall *wall, *wall1, *wall2, *wall3, *wall4;

	void DestroyTank(Tank* tank);

protected:
	void OnUpdate() override;
	void OnLoad() override;
	void OnPreDraw(Renderer* renderer) override;
};

