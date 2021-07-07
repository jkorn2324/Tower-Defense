#include "EnemyAffectorManager.h"

#include "EnemyAffectorComponent.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Level.h"
#include "CollisionComponent.h"

#include <algorithm>

namespace TowerDefense
{
    EnemyAffectorManager::EnemyAffectorManager(class Level *level)
    {
        mLevel = level;
        mEnemyManager = level->GetEnemyManager();
        mAffectors = std::vector<EnemyAffectorComponent*>();
    }

    void EnemyAffectorManager::AddAffector(EnemyAffectorComponent *affector)
    {
        const auto& affectorSearched = std::find(mAffectors.begin(), mAffectors.end(), affector);
        if(affectorSearched == mAffectors.end())
        {
            mAffectors.push_back(affector);
        }
    }

    void EnemyAffectorManager::RemoveAffector(EnemyAffectorComponent *affector)
    {
        const auto& affectorSearched = std::find(mAffectors.begin(),
                                                 mAffectors.end(), affector);
        mAffectors.erase(affectorSearched);
    }

    void EnemyAffectorManager::Update(float deltaTime)
    {
        int affectorsSize = mAffectors.size();
        for(int i = affectorsSize - 1; i >= 0; i--)
        {
            EnemyAffectorComponent* affector = mAffectors[i];
            if(!affector->IsEnabled())
            {
                continue;
            }

            const std::vector<Enemy*>& enemies = mEnemyManager->GetEnemies();
            int enemySize = static_cast<int>(enemies.size());
            for(int e = enemySize - 1; e >= 0; e--)
            {
                Enemy* enemy = enemies[e];
                CollisionComponent* collisionComponent = enemy
                        ->GetComponent<CollisionComponent>();
                CollisionData collisionData;
                if(enemy->IsActive()
                   && collisionComponent->IsEnabled()
                   && affector->Intersects(collisionComponent, collisionData))
                {
                    affector->OnCollision(enemy, collisionData);
                }
            }
        }
    }
}