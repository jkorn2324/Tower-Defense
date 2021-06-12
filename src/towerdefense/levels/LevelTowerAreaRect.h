#pragma once

#include "Vector2.h"

#include <vector>

namespace TowerDefense
{

    /**
     * Used to define an area where a tower can be placed.
     */
    struct LevelTowerAreaRect
    {
    public:
        LevelTowerAreaRect() = default;
        LevelTowerAreaRect(const Vector2& size, const Vector2& pos);

    public:
        Vector2 GetMin() const;
        Vector2 GetMax() const;
        bool IsWithinBounds(const Vector2& point) const;

    public:
        Vector2 size;
        Vector2 pos;
    };

    /**
     * Holds the areas in which the towers can be placed.
     */
    class LevelTowersAreaManager
    {
    public:
        LevelTowersAreaManager(class Level* level);
        ~LevelTowersAreaManager();

    public:
        bool CanPlaceTower(const Vector2& point) const;

    private:
        void AddTowerArea(const Vector2& size, const Vector2& pos);

    private:
        Level* mLevel;
        std::vector<LevelTowerAreaRect*> mTowerAreas;

    public:
        friend class Level;
    };
}