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
    int prevLevelIndex = -1;

    LevelInfo level1() {
        std::vector<WallInfo> wallInfos;
        // Boundaries walls
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(0, 0)));
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(97, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 77)));

        wallInfos.push_back(WallInfo(Wall(70, 3), Vector2(15, 39)));
        wallInfos.push_back(WallInfo(Wall(3, 50), Vector2(49, 15)));

        std::vector<Vector2> spawns;
        spawns.push_back(Vector2(20, 20));
        spawns.push_back(Vector2(80, 20));
        spawns.push_back(Vector2(20, 60));
        spawns.push_back(Vector2(80, 60));

        return LevelInfo(wallInfos, spawns);
    }

    LevelInfo level2() {
        std::vector<WallInfo> wallInfos;
        // Boundaries walls
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(0, 0)));
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(97, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 77)));


        wallInfos.push_back(WallInfo(Wall(20, 5), Vector2(15, 30)));
        wallInfos.push_back(WallInfo(Wall(5, 20), Vector2(35, 15)));

        wallInfos.push_back(WallInfo(Wall(20, 5), Vector2(100 - 15 - 20, 30)));
        wallInfos.push_back(WallInfo(Wall(5, 20), Vector2(100 - 35 - 5, 15)));

        wallInfos.push_back(WallInfo(Wall(20, 5), Vector2(15, 80-30-5)));
        wallInfos.push_back(WallInfo(Wall(5, 20), Vector2(35, 80-15-20)));

        wallInfos.push_back(WallInfo(Wall(20, 5), Vector2(100 - 15 - 20, 80 - 30 - 5)));
        wallInfos.push_back(WallInfo(Wall(5, 20), Vector2(100 - 35 - 5, 80 - 15 - 20)));

        wallInfos.push_back(WallInfo(Wall(4, 4), Vector2(48, 38)));

        std::vector<Vector2> spawns;
        spawns.push_back(Vector2(20, 20));
        spawns.push_back(Vector2(80, 20));
        spawns.push_back(Vector2(20, 60));
        spawns.push_back(Vector2(80, 60));

        return LevelInfo(wallInfos, spawns);
    }

    LevelInfo level3() {
        std::vector<WallInfo> wallInfos;
        // Boundaries walls
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(0, 0)));
        wallInfos.push_back(WallInfo(Wall(3, 80), Vector2(97, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 0)));
        wallInfos.push_back(WallInfo(Wall(94, 3), Vector2(3, 77)));


        wallInfos.push_back(WallInfo(Wall(20, 2), Vector2(10, 39)));
        wallInfos.push_back(WallInfo(Wall(20, 2), Vector2(100-10-20, 39)));

        wallInfos.push_back(WallInfo(Wall(2, 12), Vector2(49, 11)));
        wallInfos.push_back(WallInfo(Wall(2, 12), Vector2(49, 80-11-12)));

        wallInfos.push_back(WallInfo(Wall(20, 15), Vector2(40, 32)));

        std::vector<Vector2> spawns;
        spawns.push_back(Vector2(30, 30));
        spawns.push_back(Vector2(70, 30));
        spawns.push_back(Vector2(30, 50));
        spawns.push_back(Vector2(70, 50));

        return LevelInfo(wallInfos, spawns);
    }
};

