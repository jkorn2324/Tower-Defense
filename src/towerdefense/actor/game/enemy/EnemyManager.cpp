#include "EnemyManager.h"
#include "Enemy.h"
#include "Level.h"
#include "HealthComponent.h"

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
        const auto& enemySearched = std::find(
                mEnemies.begin(), mEnemies.end(), enemy);
        mEnemies.erase(enemySearched);
    }

    bool EnemyManager::ContainsEnemy(class Enemy *enemy)
    {
        const auto& enemySearched = std::find(
                mEnemies.begin(), mEnemies.end(), enemy);
        return enemySearched != mEnemies.end();
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
            return IsWithinRange(mEnemies[0], position, maxDist)
                ? mEnemies[0] : nullptr;
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
            return IsWithinRange(mEnemies[0], position, maxDistance)
                ? mEnemies[0] : nullptr;
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
        return GetFarthestEnemyAlongTrack(false);
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(bool countThoseThatReachedEnd) const
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
            EnemyComparisonOutput comparisonOutput =
                    CompareCandidatesAlongTrack(initialEnemy, testEnemy, countThoseThatReachedEnd);
            if(comparisonOutput == B_BETTER_THAN_A)
            {
                initialEnemy = testEnemy;
            }
        }
        return initialEnemy;
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(const Vector2& position, float maxDist) const
    {
        return GetFarthestEnemyAlongTrack(position, maxDist, false);
    }

    Enemy* EnemyManager::GetFarthestEnemyAlongTrack(const Vector2 &position, float maxDist, bool countThoseThatReachedEnd) const
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
                EnemyComparisonOutput comparisonOutput =
                        CompareCandidatesAlongTrack(initialEnemy, testEnemy, position, maxDist, countThoseThatReachedEnd);
                if(comparisonOutput == EnemyComparisonOutput::B_BETTER_THAN_A)
                {
                    initialEnemy = testEnemy;
                }
            }
        }

        if(initialEnemy->GetTargetPathNode() == nullptr)
        {
            return nullptr;
        }
        return IsWithinRange(initialEnemy, position, maxDist)
            ? initialEnemy : nullptr;
    }

    Enemy* EnemyManager::GetStrongestEnemy() const
    {
        return GetStrongestEnemy(false);
    }

    Enemy* EnemyManager::GetStrongestEnemy(bool countThoseThatReachedEnd) const
    {
        std::size_t enemiesCount = mEnemies.size();
        if(enemiesCount <= 0)
        {
            return nullptr;
        }

        if(enemiesCount == 1)
        {
            return mEnemies[0];
        }

        HealthComponent* strongestEnemyHealth = mEnemies[0]
                ->GetComponent<HealthComponent>();
        for(int i = 1; i < mEnemies.size(); i++)
        {
            HealthComponent* candidate = mEnemies[i]
                    ->GetComponent<HealthComponent>();
            if(candidate == nullptr)
            {
                continue;
            }
            if(strongestEnemyHealth == nullptr
                || candidate->GetMaxHealth() > strongestEnemyHealth->GetMaxHealth())
            {
                strongestEnemyHealth = candidate;
            }
        }
        return dynamic_cast<Enemy*>(strongestEnemyHealth->GetOwner());
    }

    Enemy* EnemyManager::GetStrongestEnemy(const Vector2 &position, float maxDist) const
    {
        return GetStrongestEnemy(position, maxDist, false);
    }

    Enemy* EnemyManager::GetStrongestEnemy(const Vector2 &position, float maxDist, bool countThoseThatReachedEnd) const
    {
        std::size_t count = mEnemies.size();
        if(count <= 0)
        {
            return nullptr;
        }
        if(count == 1)
        {
            return IsWithinRange(mEnemies[0], position, maxDist) ?
                mEnemies[0] : nullptr;
        }

        Enemy* strongestEnemy = mEnemies[0];
        HealthComponent* strongestEnemyHealth
            = strongestEnemy->GetComponent<HealthComponent>();
        for(int i = 1; i < count; i++)
        {
            // Check if candidate is within range.
            Enemy* candidateEnemy = mEnemies[i];
            if(!IsWithinRange(candidateEnemy, position, maxDist))
            {
                continue;
            }

            // If the candidate doesn't have a health component continue.
            HealthComponent* candidate = candidateEnemy->GetComponent<HealthComponent>();
            if(candidate == nullptr)
            {
                continue;
            }

            // If the strongest enemy health is null or if its not within range
            // change it to the candidate.
            if(strongestEnemyHealth == nullptr
                || !IsWithinRange(strongestEnemy, position, maxDist))
            {
                strongestEnemy = candidateEnemy;
                strongestEnemyHealth = candidate;
                continue;
            }

            // If the candidate health is greater than strongest health,
            // change it to the candidate.
            if(candidate->GetMaxHealth() > strongestEnemyHealth->GetMaxHealth())
            {
                strongestEnemy = candidateEnemy;
                strongestEnemyHealth = candidate;
                continue;
            }

            // If candidate health is equivalent to strongest health,
            // check which one is farthest down the path.
            if(candidate->GetMaxHealth() == strongestEnemyHealth->GetMaxHealth())
            {
                EnemyComparisonOutput comparisonOutput = CompareCandidatesAlongTrack(
                        strongestEnemy, candidateEnemy, position, maxDist, countThoseThatReachedEnd);
                if(comparisonOutput == EnemyComparisonOutput::B_BETTER_THAN_A)
                {
                    strongestEnemy = candidateEnemy;
                    strongestEnemyHealth = candidate;
                }
            }
        }
        return strongestEnemy;
    }

    EnemyManager::EnemyComparisonOutput EnemyManager::CompareCandidatesAlongTrack(Enemy *a, Enemy *b)
    {
        return CompareCandidatesAlongTrack(a, b, false);
    }

    EnemyManager::EnemyComparisonOutput EnemyManager::CompareCandidatesAlongTrack(Enemy *a, Enemy *b, bool countThoseThatReachedEnd)
    {
        if(a == nullptr && b == nullptr)
        {
            return EnemyComparisonOutput::NO_COMPARISON;
        }
        if(a == nullptr)
        {
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }
        if(b == nullptr)
        {
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        LevelPathNodeData* aTarget = a->GetTargetPathNode();
        LevelPathNodeData* bTarget = b->GetTargetPathNode();
        if(aTarget == nullptr && bTarget == nullptr)
        {
            return EnemyComparisonOutput::NO_COMPARISON;
        }

        if(aTarget == nullptr)
        {
            return countThoseThatReachedEnd ? EnemyComparisonOutput::A_BETTER_THAN_B
                : EnemyComparisonOutput::B_BETTER_THAN_A;
        }

        if(bTarget == nullptr)
        {
            return countThoseThatReachedEnd ? EnemyComparisonOutput::B_BETTER_THAN_A
                : EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        if(aTarget->nodeIndex > bTarget->nodeIndex)
        {
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        if(bTarget->nodeIndex > aTarget->nodeIndex)
        {
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }

        // Compare distance to the target. (currentTarget == initialTarget)
        float aDistanceToTarget = Vector2::Distance(
                a->GetTransform().GetWorldPosition(),
                aTarget->position);
        float bDistanceToTarget = Vector2::Distance(
                b->GetTransform().GetWorldPosition(),
                bTarget->position);
        if(aDistanceToTarget < bDistanceToTarget)
        {
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }
        if(bDistanceToTarget < aDistanceToTarget)
        {
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }
        return EnemyComparisonOutput::NO_COMPARISON;
    }

    EnemyManager::EnemyComparisonOutput EnemyManager::CompareCandidatesAlongTrack(Enemy* a, Enemy* b, const Vector2& position, float maxDist)
    {
        return CompareCandidatesAlongTrack(a, b, position, maxDist, false);
    }

    EnemyManager::EnemyComparisonOutput EnemyManager::CompareCandidatesAlongTrack(Enemy* a, Enemy* b, const Vector2& position, float maxDist, bool countThoseThatReachedEnd)
    {
        // If a & b are null then there was no comparison.
        if(a == nullptr && b == nullptr)
        {
            return EnemyComparisonOutput::NO_COMPARISON;
        }
        // If a is null, b must not so b is better than a.
        if(a == nullptr)
        {
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }
        // If b is null, a must not so a is better than b.
        if(b == nullptr)
        {
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        bool isAInRange = IsWithinRange(a, position, maxDist);
        bool isBInRange = IsWithinRange(b, position, maxDist);

        LevelPathNodeData* aTarget = a->GetTargetPathNode();
        LevelPathNodeData* bTarget = b->GetTargetPathNode();
        // If a target node & b target nodes are null, they both reached the end
        // so no comparison.
        if(aTarget == nullptr && bTarget == nullptr)
        {
            return EnemyComparisonOutput::NO_COMPARISON;
        }

        if(aTarget == nullptr)
        {
            bool inverseWithinRange, withinRange;
            if(countThoseThatReachedEnd)
            {
                withinRange = isAInRange;
                inverseWithinRange = isBInRange;
            }
            else
            {
                withinRange = isBInRange;
                inverseWithinRange = isAInRange;
            }

            if(!withinRange)
            {
                if(inverseWithinRange)
                {
                    return EnemyComparisonOutput::B_BETTER_THAN_A;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return countThoseThatReachedEnd ? EnemyComparisonOutput::A_BETTER_THAN_B
                : EnemyComparisonOutput::B_BETTER_THAN_A;
        }

        if(bTarget == nullptr)
        {
            bool inverseWithinRange, withinRange;
            if(countThoseThatReachedEnd)
            {
                withinRange = isBInRange;
                inverseWithinRange = isAInRange;
            }
            else
            {
                withinRange = isAInRange;
                inverseWithinRange = isBInRange;
            }

            if(!withinRange)
            {
                if(inverseWithinRange)
                {
                    return EnemyComparisonOutput::A_BETTER_THAN_B;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return countThoseThatReachedEnd ? EnemyComparisonOutput::B_BETTER_THAN_A
                : EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        if(aTarget->nodeIndex > bTarget->nodeIndex)
        {
            if(!isAInRange)
            {
                if(isBInRange)
                {
                    return EnemyComparisonOutput::B_BETTER_THAN_A;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }

        if(bTarget->nodeIndex > aTarget->nodeIndex)
        {
            if(!isBInRange)
            {
                if(isAInRange)
                {
                    return EnemyComparisonOutput::B_BETTER_THAN_A;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }

        // Compare distance to the target. (currentTarget == initialTarget)
        float aDistanceToTarget = Vector2::Distance(
                a->GetTransform().GetWorldPosition(),
                aTarget->position);
        float bDistanceToTarget = Vector2::Distance(
                b->GetTransform().GetWorldPosition(),
                bTarget->position);
        // Checks if a is closer to the target.
        if(aDistanceToTarget < bDistanceToTarget)
        {
            if(!isAInRange)
            {
                if(isBInRange)
                {
                    return EnemyComparisonOutput::B_BETTER_THAN_A;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return EnemyComparisonOutput::A_BETTER_THAN_B;
        }
        // Checks if b is closer to the target.
        if(bDistanceToTarget < aDistanceToTarget)
        {
            if(!isBInRange)
            {
                if(isAInRange)
                {
                    return EnemyComparisonOutput::A_BETTER_THAN_B;
                }
                return EnemyComparisonOutput::NO_COMPARISON;
            }
            return EnemyComparisonOutput::B_BETTER_THAN_A;
        }
        return EnemyComparisonOutput::NO_COMPARISON;
    }

    bool EnemyManager::IsWithinRange(Enemy *enemy, const Vector2 &position, float maxDist)
    {
        if(enemy == nullptr)
        {
            return false;
        }
        float distance = Vector2::Distance(
                position, enemy->GetTransform().GetWorldPosition());
        return distance <= maxDist;
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