#include <iostream>
#include <Application.h>

class Game : public Application
{
public:
    double x = 4.0, y = 4.0;
    float lx, ly, rx, ry;
    Game(const short width, const short height, const short fontW, const short fontH) : Application(width, height, fontW, fontH, 60.0f) 
    {
    }

    void OnUpdate(double delta) override {
        std::memset(renderer->buffer, 0, sizeof(CHAR_INFO) * width * height);
        
        int c = input.GetConnectedGamepadCount();
        float sx = input.GetGamepad(0)->GetStickLX();
        float sy = input.GetGamepad(0)->GetStickLY();
        lx = sx * 12 + 23;
        ly = sy * -12 + 23;
        rx = input.GetGamepad(c - 1)->GetStickRX() * 12 + 23;
        ry = input.GetGamepad(c - 1)->GetStickRY() * -12 + 23;
        x += sx;
        y -= sy;
        //x += lx;
        //y += ly;

        std::wstringstream ss;
        ss << "[Game] " << x << "," << y << std::endl;
        OutputDebugString(ss.str().c_str());
    }

    void OnRender() override {
        renderer->DrawRect(rx, ry, 2, 2, '#', 0x0c);
        renderer->DrawRect(lx, ly, 2, 2, '#', 0x09);
        renderer->DrawRect(x, y, 4, 4, '#', 0x8e);
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



