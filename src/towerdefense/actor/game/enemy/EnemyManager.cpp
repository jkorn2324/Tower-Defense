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
        std::size_t enemiesCount = mEnemies.size();
        if(enemiesCount <= 0)
        {
            return nullptr;
        }

        Enemy* initialEnemy = mEnemies[0];
        if(enemiesCount == 1)
        {
            LevelPathNodeData* initialEnemyNode = initialEnemy->GetTargetPathNode();
            return initialEnemyNode == nullptr ? initialEnemy : nullptr;
        }

        for(unsigned int i = 1; i < enemiesCount; i++)
        {
            Enemy* testEnemy = mEnemies[i];
            LevelPathNodeData* currentTarget = testEnemy->GetTargetPathNode();
            if(currentTarget == nullptr)
            {
                continue;
            }

            LevelPathNodeData* initialTargetPathNode = initialEnemy->GetTargetPathNode();
            if(initialTargetPathNode == nullptr
                || currentTarget->nodeIndex > initialTargetPathNode->nodeIndex)
            {
                initialEnemy = testEnemy;
                continue;
            }

            if(currentTarget->nodeIndex == initialTargetPathNode->nodeIndex)
            {
                const Vector2& testEnemyPos = testEnemy->GetTransform().GetWorldPosition();
                const Vector2& initialEnemyPos = initialEnemy->GetTransform().GetWorldPosition();
                float testEnemyDistance = Vector2::Distance(
                        testEnemyPos, currentTarget->position);
                float initialEnemyDistance = Vector2::Distance(
                        testEnemyPos, initialTargetPathNode->position);
                if(testEnemyDistance < initialEnemyDistance)
                {
                    initialEnemy = testEnemy;
                    continue;
                }
            }
        }
        return initialEnemy;
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(const Vector2 &position, float maxDist) const
    {
        std::size_t enemiesCount = mEnemies.size();
        if(enemiesCount <= 0)
        {
            return nullptr;
        }

        Enemy* initialEnemy = mEnemies[0];

        if(enemiesCount > 1)
        {
            for(unsigned int i = 1; i < enemiesCount; i++)
            {
                Enemy* testEnemy = mEnemies[i];
                LevelPathNodeData* currentTarget = testEnemy->GetTargetPathNode();
                if(currentTarget == nullptr)
                {
                    continue;
                }

                LevelPathNodeData* initialTarget = initialEnemy->GetTargetPathNode();
                if(initialTarget == nullptr
                   || currentTarget->nodeIndex > initialTarget->nodeIndex)
                {
                    float currentDistance = Vector2::Distance(
                            position, testEnemy->GetTransform().GetWorldPosition());
                    if(currentDistance <= maxDist)
                    {
                        initialEnemy = testEnemy;
                    }
                    continue;
                }

                if(currentTarget->nodeIndex == initialTarget->nodeIndex)
                {
                    // Compare distance to the target. (currentTarget == initialTarget)
                    float testDistanceToTarget = Vector2::Distance(
                            testEnemy->GetTransform().GetWorldPosition(),
                            currentTarget->position);
                    float initialDistanceToTarget = Vector2::Distance(
                            initialEnemy->GetTransform().GetWorldPosition(),
                            initialTarget->position);
                    if(testDistanceToTarget > initialDistanceToTarget)
                    {
                        continue;
                    }
                    // Tests the distance to the position.
                    float distanceToPosition = Vector2::Distance(
                            position, testEnemy->GetTransform().GetWorldPosition());
                    if(distanceToPosition <= maxDist)
                    {
                        initialEnemy = testEnemy;
                        continue;
                    }
                }
            }
        }

        if(initialEnemy->GetTargetPathNode() == nullptr)
        {
            return nullptr;
        }
        float currentDistance = Vector2::Distance(
                position, initialEnemy->GetTransform().GetWorldPosition());
        return currentDistance <= maxDist ? initialEnemy : nullptr;
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