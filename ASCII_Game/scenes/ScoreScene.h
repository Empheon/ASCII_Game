#pragma once
#include <scene/Scene.h>
#include <input/Gamepad.h>
#include <stack>
#include <vector>

#include "../Textures.h"
#include "../Tank.h"

class ScoreScene : public Scene
{
public:
	int playerCount;
	std::vector<Gamepad*> gamepads;
	std::vector<WORD> previousGameColors;

	ScoreScene(std::stack<Tank*> &playersStack) {
		while (!playersStack.empty()) {
			previousGameColors.push_back(playersStack.top()->color);
			playersStack.pop();
		}
	};
	~ScoreScene() {};

	static constexpr WORD playerColors[] = { 0x0c, 0x0b, 0x0a, 0x0d };

	WORD currentPlayerColors[4] = { 0x0f, 0x0f, 0x0f, 0x0f };

protected:
	void OnUpdate() override;
	void OnLoad() override;
	void OnPreDraw(Renderer* renderer) override;
};

