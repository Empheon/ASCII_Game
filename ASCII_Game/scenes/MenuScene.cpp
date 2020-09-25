#include "MenuScene.h"
#include "GameScene.h"

#define _USE_MATH_DEFINES 
#include <math.h> 

void MenuScene::OnUpdate()
{
    int readyPlayers = 0;
    for (int i = 0; i < playerCount; ++i) {
        if (gamepads[i]->IsButtonDown(XINPUT_GAMEPAD_A)) {
            currentPlayerColors[i] = playerColors[i];
        }

        if (currentPlayerColors[i] == playerColors[i]) {
            readyPlayers++;
        }
    }

    if (readyPlayers == playerCount) {
        if (!starting) {
            starting = true;
            startDelay = parent->targetFPS * START_GAME_DELAY;
        } else {
            startDelay--;

            if (startDelay <= 0) {
                parent->LoadScene(new GameScene());
            }
        }
    }
}

void MenuScene::OnLoad()
{
    playerCount = parent->input.GetConnectedGamepadCount();

    for (int i = 0; i < playerCount; ++i) {
        gamepads.push_back(parent->input.GetGamepad(i));
    }
}

void MenuScene::OnPreDraw(Renderer* renderer)
{
    renderer->Clear(' ', 0);
    if (logoColorIndex > 99999) {
        logoColorIndex = 0;
    }
    logoColorIndex += 0.015f;
    renderer->DrawTexture(50 - (TEX_LOGO.GetWidth() / 2), 20, TEX_LOGO, logoColors[(int)logoColorIndex % 7]);
    renderer->DrawTexture(50 - (TEX_PRESS_A.GetWidth() / 2), 40, TEX_PRESS_A, 0x0f);

    for (int i = 0; i < playerCount; i++) {
        renderer->DrawTexture(i * 10 + (50 - playerCount * 5) + 2, 50, TEX_TANK_BODY, currentPlayerColors[i]);
    }

    if (starting) {
        int nSusp = 3 - (startDelay / 8) % 4;
        int y = min(START_GAME_DELAY * parent->targetFPS - startDelay, 10);
        std::wstring susp(nSusp, L'.');
        renderer->DrawString(parent->width / 2 - startMessage.size() / 2, parent->height - y, startMessage + susp, 0x0f);
    }
}
