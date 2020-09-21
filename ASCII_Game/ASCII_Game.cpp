#include <iostream>
#include <Application.h>

class Game : public Application
{
public:
    Game(const short width, const short height, const short fontW, const short fontH) : Application(width, height, fontW, fontH, 60.0f) 
    {
    }
    int ble = 0;
    void onUpdate(float delta) override {
        std::memset(renderer->buffer, 0, sizeof(CHAR_INFO) * width * height);

        renderer->DrawRect((2 + ble++) % 48, (2 + ble/2) % 48, 5, 5, '\u25A0', 0x0e);
        RefreshFrame();
    }

    void onRender() override {
    }
};

int main()
{
    Game* app = new Game(48, 48, 12, 12);
    app->Run();


    std::cin.get();
    delete app;

    return 0;
}



