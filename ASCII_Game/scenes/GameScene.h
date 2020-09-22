#pragma once

#include <scene/Scene.h>
#include <input/Gamepad.h>

#include <vector>
#include "../Tank.h"
#include "../Wall.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	static constexpr WORD playerColors[] = { 0x0c, 0x0b, 0x0a, 0x0d };
	std::vector<Tank> tanks;
	Wall *wall, *wall1, *wall2, *wall3, *wall4;

protected:
	void OnUpdate() override;
	void OnLoad() override;
	void OnPreDraw(Renderer* renderer) override;
};

