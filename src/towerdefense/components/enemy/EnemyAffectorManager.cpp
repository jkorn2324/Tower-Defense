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
        for(const auto& affector : mAffectors)
        {
            if(!affector->IsEnabled())
            {
                continue;
            }
            for(const auto& enemy : mEnemyManager->GetEnemies())
            {
                CollisionComponent* collisionComponent = enemy
                        ->GetComponent<CollisionComponent>();
                CollisionData collisionData;
                if(affector->Intersects(collisionComponent, collisionData))
                {
                    affector->OnCollision(enemy, collisionData);
                }
            }
        }
    }
}