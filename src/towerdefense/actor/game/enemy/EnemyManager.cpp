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

    Enemy* EnemyManager::GetClosestEnemy(const Vector2 &position, float maxDist) const
    {
        std::size_t size = mEnemies.size();
        if(size <= 0)
        {
            return nullptr;
        }

        if(size == 1)
        {
            auto enemy = mEnemies[0];
            float distance = Vector2::Distance(
                    enemy->GetTransform().GetPosition(), position);
            return distance <= maxDist ? mEnemies[0] : nullptr;
        }

        auto closestEnemy = mEnemies[0];
        float minimumDistance = Vector2::Distance(
                closestEnemy->GetTransform().GetPosition(), position);
        for(unsigned int i = 1; i < size; i++)
        {
            const auto& enemyTest = mEnemies[i];
            float distanceTest = Vector2::Distance(
                    enemyTest->GetTransform().GetPosition(), position);
            if(distanceTest <= maxDist
                && (minimumDistance > maxDist
                || distanceTest <= minimumDistance))
            {
                minimumDistance = distanceTest;
                closestEnemy = enemyTest;
            }
        }
        return minimumDistance <= maxDist ? closestEnemy : nullptr;
    }

    Enemy* EnemyManager::GetFarthestEnemy(const Vector2 &position) const
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

        Enemy* farthestEnemy = mEnemies[0];
        const Vector2& worldPosition = farthestEnemy
                ->GetTransform().GetWorldPosition();
        float distance = Vector2::Distance(worldPosition, position);
        for(unsigned int i = 1; i < (unsigned int)size; i++)
        {
            Enemy* enemy = mEnemies[i];
            const Vector2& testWorldPos = enemy
                    ->GetTransform().GetWorldPosition();
            float testDistance = Vector2::Distance(testWorldPos, position);
            if(testDistance > distance)
            {
                farthestEnemy = enemy;
                distance = testDistance;
            }
        }
        return farthestEnemy;
    }

    Enemy* EnemyManager::GetFarthestEnemy(const Vector2 &position, float maxDistance) const
    {
        std::size_t size = mEnemies.size();
        if(size <= 0)
        {
            return nullptr;
        }

        if(size == 1)
        {
            auto enemy = mEnemies[0];
            float distance = Vector2::Distance(
                    enemy->GetTransform().GetPosition(), position);
            return distance <= maxDistance ? mEnemies[0] : nullptr;
        }

        Enemy* farthestEnemy = mEnemies[0];
        const Vector2& worldPosition = farthestEnemy
                ->GetTransform().GetWorldPosition();
        float distance = Vector2::Distance(worldPosition, position);
        for(unsigned int i = 1; i < (unsigned int)size; i++)
        {
            Enemy* enemy = mEnemies[i];
            const Vector2& testWorldPos = enemy
                    ->GetTransform().GetWorldPosition();
            float testDistance = Vector2::Distance(testWorldPos, position);
            if(testDistance <= maxDistance
                && (distance > maxDistance
                    || testDistance > distance))
            {
                farthestEnemy = enemy;
                distance = testDistance;
            }
        }
        return distance <= maxDistance ? farthestEnemy : nullptr;
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack() const
    {
        // TODO: Implementation
        return nullptr;
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(const Vector2 &position) const
    {
        // TODO: Implementation
        return nullptr;
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(const Vector2 &position, float maxDist) const
    {
        // TODO: Implementation
        return nullptr;
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