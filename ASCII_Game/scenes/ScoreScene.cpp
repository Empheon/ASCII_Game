#include "ScoreScene.h"
#include "GameScene.h"

void ScoreScene::OnUpdate()
{
    if (!(parent->GetAppTicks() % 60) && parent->input.SearchGamepads()) {
        playerCount = parent->input.GetConnectedGamepadCount();
        gamepads.clear();
        for (int i = 0; i < playerCount; ++i) {
            gamepads.push_back(parent->input.GetGamepad(i));
        }
    }

    int readyPlayers = 0;
    for (int i = 0; i < playerCount; ++i) {
        if (gamepads[i]->IsButtonDown(XINPUT_GAMEPAD_A)) {
            currentPlayerColors[i] = playerColors[i];
        }

        if (currentPlayerColors[i] == playerColors[i]) {
            readyPlayers++;
        }
    }

    if (playerCount > 0 && readyPlayers == playerCount) {
        parent->LoadScene(new GameScene());
    }
}

void ScoreScene::OnLoad()
{
    playerCount = parent->input.GetConnectedGamepadCount();

    for (int i = 0; i < playerCount; ++i) {
        gamepads.push_back(parent->input.GetGamepad(i));
    }
}

void ScoreScene::OnPreDraw(Renderer* renderer)
{
    parent->renderer->Clear(' ', 0x07);
    parent->renderer->DrawTexture(50 - (TEX_SCOREBOARD_TEXT.GetWidth() / 2), 15, TEX_SCOREBOARD_TEXT, previousGameColors[0]);

    for (int i = 0; i < previousGameColors.size(); i++) {
        WORD color = previousGameColors[i];
        parent->renderer->DrawTexture(30, 23 + i * 10, TEX_SCORE_NUMBERS[i], color);
        parent->renderer->DrawTexture(50 - 2, 23 + 1 + i * 10, TEX_TANK_BODY, color);
    }


    if (playerCount <= 0) {
        renderer->DrawString(parent->width / 2 - missingDevice.size() / 2, 62, missingDevice, 0x0f);
    }
    else {

        parent->renderer->DrawTexture(50 - (TEX_PRESS_A.GetWidth() / 2), 60, TEX_PRESS_A, 0x0f);

        for (int i = 0; i < playerCount; i++) {

            parent->renderer->DrawTexture(i * 10 + (50 - playerCount * 5) + 2, 70, TEX_TANK_BODY, currentPlayerColors[i]);
        }
    }
}
