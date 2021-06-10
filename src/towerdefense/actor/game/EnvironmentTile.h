#pragma once

#include "Actor.h"

namespace TowerDefense
{

    class EnvironmentTile : public Actor
    {
    public:
        EnvironmentTile(struct LevelTileData* tileData, class Level* level);

    private:
        class TileSpriteComponent* mSpriteComponent;
        class Level* mLevel;
    };
}