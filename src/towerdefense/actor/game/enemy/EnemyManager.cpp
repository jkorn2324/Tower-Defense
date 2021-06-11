#include "EnemyManager.h"
#include "Enemy.h"
#include "Level.h"

#include <algorithm>

namespace TowerDefense
{

    EnemyManager::EnemyManager(class Level *level)
    {
        mEnemies = std::vector<Enemy*>();
        mCurrentLevel = level;
        mSpawnPosition = Vector2::Zero();
    }

    Level* EnemyManager::GetLevel() const
    {
        return mCurrentLevel;
    }

    void EnemyManager::SetSpawnPosition(const Vector2 &spawnPosition)
    {
        mSpawnPosition = spawnPosition;
    }

    const Vector2& EnemyManager::GetSpawnPosition() const
    {
        return mSpawnPosition;
    }

    void EnemyManager::AddEnemy(Enemy *enemy)
    {
        mEnemies.push_back(enemy);
    }

    void EnemyManager::RemoveEnemy(Enemy *enemy)
    {
        const auto& enemySearched = std::find(mEnemies.begin(), mEnemies.end(), enemy);
        mEnemies.erase(enemySearched);
    }

    Enemy* EnemyManager::GetClosestEnemy(const Vector2 &position) const
    {
        std::size_t size = mEnemies.size();
        if(size <= 0)
        {
            return nullptr;
        }

        if(size == 1)
        {
            return mEnemies[0];
        }

        auto closestEnemy = mEnemies[0];
        float minimumDistance = Vector2::Distance(
                closestEnemy->GetTransform().GetPosition(), position);
        for(unsigned int i = 1; i < size; i++)
        {
            const auto& enemyTest = mEnemies[i];
            float distanceTest = Vector2::Distance(
                    enemyTest->GetTransform().GetPosition(), position);
            if(distanceTest < minimumDistance)
            {
                minimumDistance = distanceTest;
                closestEnemy = enemyTest;
            }
        }
        return closestEnemy;
    }

    const std::vector<Enemy*>& EnemyManager::GetEnemies() const
    {
        return mEnemies;
    }

    void EnemyManager::ClearEnemies()
    {
        for(const auto& enemy : mEnemies)
        {
            enemy->Despawn();
        }
        mEnemies.clear();
    }
}