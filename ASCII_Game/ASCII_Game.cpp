#include <iostream>
#include <Application.h>

class Game : public Application
{
public:
    Game(const short width, const short height, const short fontW, const short fontH) : Application(width, height, fontW, fontH, 30.0f) 
    {
    }

    void onUpdate(float delta) override {
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



