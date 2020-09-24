#pragma once

#include <scene/Scene.h>
#include <input/Gamepad.h>

#include <vector>
#include <stack>
#include "../Tank.h"
#include "../Wall.h"
#include "../LevelInfo.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    int playerCount;


    static constexpr WORD playerColors[] = { 0x0c, 0x0b, 0x0a, 0x0d };
    std::vector<Tank> tanks;
    std::stack<Tank*> destroyedTanks;

    std::vector<LevelInfo> levels;

    void DestroyTank(Tank* tank);

protected:
    void OnUpdate() override;
    void OnLoad() override;
    void OnPreDraw(Renderer* renderer) override;

private:
    LevelInfo level1() {
        std::vector<WallInfo> wallInfos;
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(0, 0)));
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(97, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 77)));

        std::vector<Vector2> spawns;
        spawns.push_back(Vector2(20, 20));
        spawns.push_back(Vector2(80, 20));
        spawns.push_back(Vector2(20, 60));
        spawns.push_back(Vector2(80, 60));

        return LevelInfo(wallInfos, spawns);
    }
};

