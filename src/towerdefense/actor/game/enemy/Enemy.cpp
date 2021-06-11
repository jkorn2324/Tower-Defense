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

namespace TowerDefense
{

    Enemy::Enemy(Game *game)
        : Actor(game)
    {
        mLevel = game->GetLevelManager()->GetActiveLevel();
        EnemyManager* enemyManager = mLevel->GetEnemyManager();
        mTransform.SetPosition(enemyManager->GetSpawnPosition());

        mCollisionComponent = new CollisionComponent(this);
        mEnemyAIComponent = new EnemyAIComponent(this, mLevel);
        mEnemyAIComponent->SetMovementSpeed(100.0f);

        mSpriteComponent = new TileSpriteComponent(this);
        mSpriteComponent->SetSizeChangedCallback(std::bind(
                &Enemy::OnSizeChanged, this, std::placeholders::_1));
        ((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
        mSpriteComponent->SetTileSize(static_cast<float>(TILE_SIZE_X),
                                      static_cast<float>(TILE_SIZE_Y));
        mSpriteComponent->SetTileIndex(245);

        enemyManager->AddEnemy(this);
    }

    Enemy::~Enemy()
    {
        mLevel->GetEnemyManager()->RemoveEnemy(this);
    }

    void Enemy::OnUpdate(float deltaTime)
    {
        // TODO: Implementation
    }

    void Enemy::OnSizeChanged(const Vector2 &size)
    {
        mCollisionComponent->SetSize(size);
    }
}