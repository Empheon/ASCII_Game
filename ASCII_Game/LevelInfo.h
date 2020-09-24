#pragma once
#include <vector>

#include "Wall.h"

class LevelInfo
{
public:
    std::vector<WallInfo> walls;
    std::vector<Vector2> spawns;

    LevelInfo(std::vector<WallInfo> walls, std::vector<Vector2> spawns) : walls(walls), spawns(spawns) {};
    ~LevelInfo() {};

    void Init() {

    }
};

