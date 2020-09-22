#include <iostream>
#include <Application.h>
#include <render/Texture.h>

#include "Textures.h"
#include "Tank.h"



class Game : public Application
{
public:
    float x = 4.0, y = 4.0;
    float lx, ly, rx, ry;

    int playerCount;
    Texture tx;

    Tank tanks[2];

    std::vector<std::pair<float, float>> points;
    Game(const short width, const short height, const short fontW, const short fontH)
        : Application(width, height, fontW, fontH, 60.0f), tx(TEX_TANK_BODY)
    {
        playerCount = input.GetConnectedGamepadCount();

        tanks[0] = Tank(0x0b, input.GetGamepad(0));
        tanks[1] = Tank(0x0c, input.GetGamepad(playerCount > 1 ? 1 : 0));
    }

    void OnUpdate(double delta) override {
        std::memset(renderer->buffer, 0, sizeof(CHAR_INFO) * width * height);
        
        /*float sx = input.GetGamepad(0)->GetStickLX();
        float sy = input.GetGamepad(0)->GetStickLY();
        lx = sx * 12 + 23;
        ly = sy * -12 + 23;
        rx = input.GetGamepad(c - 1)->GetStickRX() * 12 + 23;
        ry = input.GetGamepad(c - 1)->GetStickRY() * -12 + 23;
        x += sx;
        y -= sy;
        if (x < -4.0f) x = 100.0f;
        if (y < -4.0f) y = 100.0f;
        if (x > 100.0f) x = -4.0f;
        if (y > 100.0f) y = -4.0f;*/

        for (Tank& t : tanks)
        {
            t.Update();
        }

        if (input.GetGamepad(0)->IsButtonDown(XINPUT_GAMEPAD_B)) {
            points.push_back(std::make_pair(x, y));
        }
    }

    void OnRender() override {
        renderer->DrawRect(0, 0, width, height, '.', 0x08);
        renderer->DrawRect(rx, ry, 2, 2, '#', 0x0c);
        renderer->DrawRect(lx, ly, 2, 2, '#', 0x0b);
        //renderer->DrawRect(x, y, 4, 4, '#', 0x8e);
        renderer->DrawSprite(x, y, tx, 0x0b);

        for (auto& p : points) {
            renderer->DrawChar(p.first, p.second, 'O', 0x0a);
        }

        for (Tank& t : tanks)
        {
            t.Draw();
        }
        RefreshFrame();
    }
};



int main()
{
    Game* app = new Game(100, 80, 8, 8);
    app->Run();

    std::cin.get();
    delete app;

    return 0;
}



