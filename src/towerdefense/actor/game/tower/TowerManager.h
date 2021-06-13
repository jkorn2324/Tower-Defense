#pragma once

#include "Vector2.h"

#include <vector>

namespace TowerDefense
{

    class TowerManager
    {
    private:
        struct TowerData
        {
            class Tower* tower;
            float distance;
        };

    public:
        explicit TowerManager(class Level* level);

    public:
        const std::vector<class Tower*>& GetTowers() const;
        class Level* GetLevel() const;
        class Tower* GetTowerAtPosition(const Vector2& position) const;

    private:
        bool CanPlaceTower(const Vector2& point) const;
        void AddTower(class Tower* tower);
        void RemoveTower(class Tower* tower);
        void ClearTowers();

    private:
        std::vector<class Tower*> mTowers;
        class Level* mLevel;
        class Game* mGame;

    public:
        friend class Tower;
        friend class Level;
    };
}