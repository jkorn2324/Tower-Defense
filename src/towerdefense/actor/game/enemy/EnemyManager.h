#pragma once

#include <vector>
#include "Vector2.h"

namespace TowerDefense
{

    class EnemyManager
    {
    public:
        enum EnemyComparisonOutput
        {
            A_BETTER_THAN_B,
            B_BETTER_THAN_A,
            NO_COMPARISON
        };

    public:
        explicit EnemyManager(class Level* level);

    public:
        class Level* GetLevel() const;
        const std::vector<class Enemy*>& GetEnemies() const;

    public:
        class Enemy* GetClosestEnemy(const Vector2& position) const;
        class Enemy* GetClosestEnemy(const Vector2& position, float maxDist) const;
        class Enemy* GetFarthestEnemy(const Vector2& position) const;
        class Enemy* GetFarthestEnemy(const Vector2& position, float maxDist) const;
        class Enemy* GetFarthestEnemyAlongTrack() const;
        class Enemy* GetFarthestEnemyAlongTrack(const Vector2& position, float maxDist) const;
        class Enemy* GetStrongestEnemy() const;
        class Enemy* GetStrongestEnemy(const Vector2& position, float maxDist) const;

    public:
        const Vector2& GetSpawnPosition() const;
        bool ContainsEnemy(class Enemy* enemy);

    private:
        static bool IsWithinRange(Enemy* enemy, const Vector2& position, float maxDist);
        static EnemyComparisonOutput CompareCandidatesAlongTrack(Enemy* a, Enemy* b);
        static EnemyComparisonOutput CompareCandidatesAlongTrack(Enemy* a, Enemy* b, const Vector2& position, float maxDist);

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