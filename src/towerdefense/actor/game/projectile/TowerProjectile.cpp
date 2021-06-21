#include "TowerProjectile.h"

#include "Game.h"
#include "LevelManager.h"
#include "Level.h"

#include "MoveComponent.h"
#include "EnemyAffectorComponent.h"

#include <functional>

namespace TowerDefense
{

    TowerProjectile::TowerProjectile(Game *game)
        : Actor(game)
    {
        mMoveComponent = new MoveComponent(this);
        mEnemyAffectorComponent = new EnemyAffectorComponent(this);
        mEnemyAffectorComponent->SetSize(5.0f, 5.0f);
        mEnemyAffectorComponent->SetEnemyCollisionCallback(
                std::bind(&TowerProjectile::OnEnemyCollision, this, std::placeholders::_1));

        mLevel = game->GetLevelManager()->GetActiveLevel();
        mLevel->AddActor(this);
    }

    TowerProjectile::~TowerProjectile()
    {
        mLevel->RemoveActor(this);
    }

    Level* TowerProjectile::GetLevel() const { return mLevel; }
}