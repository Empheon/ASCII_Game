#pragma once
#include <scene/Scene.h>
#include <input/Gamepad.h>
#include <vector>

#include "../Textures.h"

#define START_GAME_DELAY 2.0

class MenuScene : public Scene
{
public:
	WORD logoColor;
	float logoColorIndex = 0;
	WORD currentPlayerColors[4] = { 0x0f, 0x0f, 0x0f, 0x0f };

	int playerCount;
	std::vector<Gamepad*> gamepads;

	MenuScene() {};
	~MenuScene() {};

	static constexpr WORD playerColors[] = { 0x0c, 0x0b, 0x0a, 0x0d };
	static constexpr WORD logoColors[] = { 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

protected:
	void OnUpdate() override;
	void OnLoad() override;
	void OnPreDraw(Renderer* renderer) override;

private:
	bool starting = false;
	int startDelay;
	const std::wstring startMessage = L"Everybody is ready, starting the game ";
	const std::wstring missingDevice = L"No game controller was detected, please plug one.";
};

