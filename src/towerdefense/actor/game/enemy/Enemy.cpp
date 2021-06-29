#include "Enemy.h"
#include "Game.h"
#include "GameParameters.h"
#include "Level.h"
#include "LevelManager.h"
#include "EnemyManager.h"

#include "TileSpriteComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "EnemyAIComponent.h"
#include "HealthComponent.h"
#include "ScaleSelectAnimationComponent.h"

namespace TowerDefense
{

    EnemyType GetEnemyTypeFromLocalizedString(const std::string& string)
    {
        if(string == "green-enemy")
        {
            return EnemyType::GREEN_ENEMY;
        }
        return EnemyType::UNKNOWN;
    }

    Enemy::Enemy(Game *game)
        : Actor(game)
    {
        mLevel = game->GetLevelManager()->GetActiveLevel();
        EnemyManager* enemyManager = mLevel->GetEnemyManager();
        mTransform.SetPosition(enemyManager->GetSpawnPosition());

        mCollisionComponent = new CollisionComponent(this);
        mCollisionComponent->SetSize(20.0f, 20.0f);

        mEnemyAIComponent = new EnemyAIComponent(this, mLevel);
        mEnemyAIComponent->SetMovementSpeed(100.0f);

        mHealthComponent = new HealthComponent(this);
        mHealthComponent->SetHealthChangedCallback(
                std::bind(&Enemy::OnHealthChanged, this, std::placeholders::_1));

        enemyManager->AddEnemy(this);
    }

    Enemy::~Enemy()
    {
        mLevel->GetEnemyManager()->RemoveEnemy(this);
    }

    struct LevelPathNodeData* Enemy::GetTargetPathNode() const
    {
        return mEnemyAIComponent->GetTargetPathNode();
    }

    void Enemy::OnHealthChanged(const HealthChangedEventData &eventData)
    {
        if(eventData.newHealth <= 0.0f)
        {
            Despawn();
        }
    }
}