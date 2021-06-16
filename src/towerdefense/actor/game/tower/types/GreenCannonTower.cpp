#include "GreenCannonTower.h"

#include "Enemy.h"
#include "Transform.h"
#include "Game.h"
#include "GameParameters.h"
#include "Actor.h"
#include "TileSpriteComponent.h"
#include "SpriteComponent.h"

namespace TowerDefense
{
    GreenCannonTower::GreenCannonTower(Game *game)
            : Tower(game)
    {
        mRange = GREEN_CANNON_ORIGINAL_RANGE;
        mCannon = GenerateCannon();
        mSpriteComponent->SetTileIndex(180);
    }

    Actor* GreenCannonTower::GenerateCannon()
    {
        Actor* actor = new Actor(mGame);
        actor->SetParent(this);

        Transform& cannonTransform = (Transform&)actor->GetTransform();
        cannonTransform.SetRotation(90.0f);

        TileSpriteComponent* tileSprite = new TileSpriteComponent(actor);
        ((SpriteComponent*)tileSprite)->SetTexture(TILESHEET_PATH);
        tileSprite->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
        tileSprite->SetTileIndex(249);
        tileSprite->SetDrawLayer(2);
        tileSprite->SetRotationOffset(-90.0f);
        return actor;
    }

    void GreenCannonTower::UpdateNonPlacedTower(float deltaTime) { }

    void GreenCannonTower::UpdatePlacedTower(float deltaTime)
    {
        if(mTarget != nullptr)
        {
            const Vector2& targetPosition = mTarget->GetTransform().GetWorldPosition();
            Transform& cannonTransform = (Transform&)mCannon->GetTransform();
            cannonTransform.LookAt(targetPosition);
        }
    }

    float GreenCannonTower::GetRange() const { return mRange; }

    void GreenCannonTower::OnDespawn()
    {
        mCannon->Despawn();
    }
}