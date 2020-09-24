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
        parent->LoadScene(new GameScene());
    }

    Vector2 pos = { parent->width / 2.0f, parent->height - 20.0f };
    if (parent->GetAppTicks() % 5 == 0) {
        ParticleInfo info = PART_BOUNCE;
        info.direction = ((float)rand() / RAND_MAX) * 2 * M_PI;
        float offx = 0.0f;// ((float)rand() / RAND_MAX) * 20 - 10;
        float offy = 0.0f;// ((float)rand() / RAND_MAX) * 2;
        parent->particles.Emit(info, {pos.x + offx, pos.y + offy});
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
}
