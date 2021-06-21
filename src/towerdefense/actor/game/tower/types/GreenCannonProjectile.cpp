#include "GreenCannonProjectile.h"

#include "EnemyAffectorComponent.h"
#include "TileSpriteComponent.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "GameParameters.h"
#include "GameMath.h"
#include "HealthComponent.h"
#include "Enemy.h"

namespace TowerDefense
{

    GreenCannonProjectile::GreenCannonProjectile(class Game *game)
            : TowerProjectile(game)
    {
        mTarget = nullptr;
        mSpriteComponent = new TileSpriteComponent(this);
        ((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
        mSpriteComponent->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
        mSpriteComponent->SetTileIndex(272);
        mMoveComponent->SetMovementSpeed(GREEN_CANNON_PROJECTILE_SPEED);
    }

    void GreenCannonProjectile::SetTarget(class Actor *target)
    {
        mTarget = target;
    }

    void GreenCannonProjectile::OnUpdate(float deltaTime)
    {
        if(mTarget != nullptr)
        {
            mTransform.LookAt(mTarget
            ->GetTransform().GetWorldPosition());
        }
    }

    void GreenCannonProjectile::OnEnemyCollision(const EnemyCollisionData &collisionData)
    {
        SDL_Log("Projectile has collided with an enemy");
        HealthComponent* healthComponent = collisionData.enemy
                ->GetComponent<HealthComponent>();
        if(healthComponent != nullptr)
        {
            float currentHealth = healthComponent->GetHealth();
            healthComponent->SetHealth(currentHealth - 5.0f);
        }
        Despawn();
    }
}