#pragma once

#include <vector>
#include "Vector2.h"

namespace TowerDefense
{

    class EnemyManager
    {
    public:
        explicit EnemyManager(class Level* level);

    public:
        class Level* GetLevel() const;
        const std::vector<class Enemy*>& GetEnemies() const;
        class Enemy* GetClosestEnemy(const Vector2& position) const;
        // TODO: Get Enemy closest to the goal

    public:
        const Vector2& GetSpawnPosition() const;

    private:
        void SetSpawnPosition(const Vector2& spawnPosition);
        void ClearEnemies();
        void AddEnemy(class Enemy* enemy);
        void RemoveEnemy(class Enemy* enemy);

    private:
        std::vector<class Enemy*> mEnemies;
        class Level* mCurrentLevel;
        Vector2 mSpawnPosition;

    public:
        friend class Level;
        friend class Enemy;
    };
}