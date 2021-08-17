#include "GreenCannonProjectile.h"

#include "EnemyAffectorComponent.h"
#include "TileSpriteComponent.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "GameParameters.h"
#include "GameMath.h"
#include "HealthComponent.h"
#include "Enemy.h"

#include <functional>

namespace TowerDefense
{

    GreenCannonProjectile::GreenCannonProjectile(class Game *game)
            : TowerProjectile(game)
    {
        mTarget = nullptr;
        mHitEnemy = false;
        mDespawnObserver = nullptr;
        mSpriteComponent = new TileSpriteComponent(this);
        ((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
        mSpriteComponent->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
        mSpriteComponent->SetTileIndex(272);
        mMoveComponent->SetMovementSpeed(GREEN_CANNON_PROJECTILE_SPEED);
    }

    GreenCannonProjectile::~GreenCannonProjectile()
    {
        mTarget = nullptr;
        delete mDespawnObserver;
    }

    void GreenCannonProjectile::SetTarget(class Actor *target)
    {
        mTarget = target;
        delete mDespawnObserver;

        if(mTarget != nullptr)
        {
            // Deallocates new memory for the observer.
            mDespawnObserver = new ActorDespawnObserver(target);
            mDespawnObserver->SetCallback(
                    std::bind(&GreenCannonProjectile::OnTargetDespawn, this, std::placeholders::_1));
        }
    }

    void GreenCannonProjectile::OnUpdate(float deltaTime)
    {
        if(mTarget != nullptr && !mHitEnemy)
        {
            mTransform.LookAt(mTarget
                ->GetTransform().GetWorldPosition());
        }
    }

    void GreenCannonProjectile::OnEnemyCollision(const EnemyCollisionData &collisionData)
    {
        if(mHitEnemy)
        {
           return;
        }

        mHitEnemy = true;
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

    void GreenCannonProjectile::OnTargetDespawn(class Actor *actor)
    {
        // Sets the target to null when it despawns.
        // Prevents a null pointer exception when it tries to look for a target.
        mTarget = nullptr;
    }
}