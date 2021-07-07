#include "GreenCannonTower.h"

#include "Enemy.h"
#include "Transform.h"
#include "Game.h"
#include "GameParameters.h"
#include "Actor.h"
#include "TileSpriteComponent.h"
#include "SpriteComponent.h"
#include "GameMath.h"
#include "GreenCannonProjectile.h"
#include "ScaleSelectAnimationComponent.h"
#include "MoveComponent.h"
#include "EnemyManager.h"

namespace TowerDefense
{
    GreenCannonTower::GreenCannonTower(Game *game)
            : Tower(game)
    {
        mRange = GREEN_CANNON_ORIGINAL_RANGE;
        mMaxProjectileCooldown = GREEN_CANNON_ORIGINAL_PROJECTILE_COOLDOWN;
        mProjectileCooldown = 0.01f;

        mCannon = GenerateCannon();
        mSpriteComponent->SetTileIndex(180);
    }

    Actor* GreenCannonTower::GenerateCannon()
    {
        Actor* actor = new Actor(mGame);
        actor->SetParent(this);

        Transform& cannonTransform = (Transform&)actor->GetTransform();
        cannonTransform.SetRotation(90.0f);

        ScaleSelectAnimationComponent* selectAnimationComponent
            = new ScaleSelectAnimationComponent(actor);
        selectAnimationComponent->SetTotalAnimationTime(
                mScaleSelectAnimationComponent->GetTotalAnimationTime());
        selectAnimationComponent->SetMaxScale(
                mScaleSelectAnimationComponent->GetMaxScale());

        TileSpriteComponent* tileSprite = new TileSpriteComponent(actor);
        ((SpriteComponent*)tileSprite)->SetTexture(TILESHEET_PATH);
        tileSprite->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
        tileSprite->SetTileIndex(249);
        tileSprite->SetDrawLayer(
                mSpriteComponent->GetDrawLayer() + 1);
        tileSprite->SetRotationOffset(-90.0f);
        return actor;
    }

    void GreenCannonTower::GenerateProjectile()
    {
        GreenCannonProjectile* projectile = new GreenCannonProjectile(mGame);
        Transform& transform = (Transform&)projectile->GetTransform();
        transform.SetPosition(mCannon->GetTransform().GetWorldPosition()
            + mCannon->GetTransform().GetForward() * 5.0f);
        transform.SetRotation(mCannon->GetTransform().GetRotation(), true);
        projectile->SetTarget(mTarget);
    }

    void GreenCannonTower::OnSelected()
    {
        Tower::OnSelected();

        ScaleSelectAnimationComponent* scaleSelectAnimationComponent
            = mCannon->GetComponent<ScaleSelectAnimationComponent>();
        if(scaleSelectAnimationComponent != nullptr)
        {
            scaleSelectAnimationComponent->TriggerAnimation();
        }
    }

    void GreenCannonTower::UpdateNonPlacedTower(float deltaTime) { }

    void GreenCannonTower::UpdatePlacedTower(float deltaTime)
    {
        Transform& cannonTransform = (Transform&)mCannon->GetTransform();
        if(mTarget != nullptr)
        {
            // TODO: Crash here.
            Vector2 targetPosition = mTarget->GetTransform().GetWorldPosition();
            cannonTransform.LookAt(targetPosition);
        }
        UpdateProjectile(deltaTime);
    }

    void GreenCannonTower::UpdateProjectile(float deltaTime)
    {
        if(mTarget != nullptr)
        {
            if(mProjectileCooldown > 0.0f)
            {
                mProjectileCooldown -= deltaTime;
                if(mProjectileCooldown <= 0.0f)
                {
                    // Shoots the projectile.
                    mProjectileCooldown = mMaxProjectileCooldown;
                    GenerateProjectile();
                }
            }
        }
    }

    float GreenCannonTower::GetRange() const { return mRange; }

    void GreenCannonTower::OnDespawn()
    {
        mCannon->Despawn();
    }
}