#include "EnemyAffectorComponent.h"

#include "Actor.h"
#include "Game.h"
#include "LevelManager.h"
#include "Level.h"
#include "EnemyAffectorManager.h"

namespace TowerDefense
{

    EnemyAffectorComponent::EnemyAffectorComponent(class Actor *owner)
            : CollisionComponent(owner)
    {
        mEnemyCollisionCallback = EventCallback<const EnemyCollisionData&>();
        mLevel = owner->GetGame()->GetLevelManager()->GetActiveLevel();
        mLevel->GetEnemyAffectorManager()->AddAffector(this);
    }

    EnemyAffectorComponent::~EnemyAffectorComponent()
    {
        mLevel->GetEnemyAffectorManager()->RemoveAffector(this);
    }

    void EnemyAffectorComponent::SetEnemyCollisionCallback(std::function<void(const EnemyCollisionData &)> callback)
    {
        mEnemyCollisionCallback.SetCallback(callback);
    }

    void EnemyAffectorComponent::OnCollision(class Enemy *enemy,
            const CollisionData& collisionData)
    {
        EnemyCollisionData enemyCollisionData;
        enemyCollisionData.collisionData = collisionData;
        enemyCollisionData.enemy = enemy;
        mEnemyCollisionCallback.Invoke(enemyCollisionData);
    }
}