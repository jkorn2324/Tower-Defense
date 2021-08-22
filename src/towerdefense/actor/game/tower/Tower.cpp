#include "Tower.h"
#include "Game.h"
#include "TileSpriteComponent.h"
#include "Texture.h"
#include "GameParameters.h"
#include "CollisionComponent.h"
#include "LevelManager.h"
#include "TowerManager.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Level.h"
#include "SpriteComponent.h"
#include "MouseObserverComponent.h"
#include "ScaleSelectAnimationComponent.h"
#include "GreenCannonTower.h"

#include <functional>

namespace TowerDefense
{
	
	Tower::Tower(Game* game)
		: Actor(game)
	{
	    mTarget = nullptr;
	    mRangeHighlight = SetupRangeHighlight();
	    mTargetType = TowerTargetType::TARGET_FARTHEST_ALONG_TRACK;
		mCollisionComponent = new CollisionComponent(this);
		mCollisionComponent->SetSize(1.0f, 1.0f);

        mScaleSelectAnimationComponent = new ScaleSelectAnimationComponent(this);
        mScaleSelectAnimationComponent->SetMaxScale(1.1f, 1.1f);
        mScaleSelectAnimationComponent->SetTotalAnimationTime(0.15f);
        mScaleSelectAnimationComponent->SetEnabled(false);

		mPlaced = false;
		mHighlighted = false;

		mLevel = game->GetLevelManager()->GetActiveLevel();
        mTowerType = TowerType::DEFAULT_TOWER_TYPE;
		mSpriteComponent = new TileSpriteComponent(this,
			std::bind(&Tower::OnSizeChanged, this, std::placeholders::_1));
		((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
		mSpriteComponent->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
		mSpriteComponent->SetTileIndex(130);
		mSpriteComponent->SetDrawLayer(30.0f);

		mEnemyManager = mLevel->GetEnemyManager();
		GenerateName();
		mLevel->GetTowerManager()->AddTower(this);
	}

    Tower::~Tower()
    {
	    mRangeHighlight->Despawn();
    }

    Actor* Tower::SetupRangeHighlight()
    {
	    Actor* actor = new Actor(mGame);
        actor->SetParent(this);
	    SpriteComponent* spriteComponent = new SpriteComponent(actor);
        spriteComponent->SetTexture("Assets/Sprites/white_circle.png");
        spriteComponent->SetDrawLayer(10);
        Color colorMultiplier = Color::GetWhite();
        colorMultiplier.a = 0.2f;
        spriteComponent->SetColorMultiplier(colorMultiplier);
	    return actor;
    }

    void Tower::GenerateName()
    {
	    switch(mTowerType)
        {
            case TowerType::DEFAULT_TOWER_TYPE:
                mName = "Default Tower";
                break;
            case TowerType::GREEN_CANNON_TOWER_TYPE:
                mName = "Green Cannon Tower";
                break;
        }
    }

    void Tower::OnSelected()
    {
        mScaleSelectAnimationComponent->TriggerAnimation();
    }

    void Tower::OnSpawn()
    {
        HighlightTowerRange(mHighlighted);
    }

    void Tower::OnDespawn()
    {
        mLevel->GetTowerManager()->RemoveTower(this);
    }

    void Tower::HighlightTowerRange(bool highlight)
    {
        SpriteComponent* highlightSprite = mRangeHighlight->GetComponent
                <SpriteComponent>();
        highlightSprite->SetSize(
                GetRange() * 2.0f, GetRange() * 2.0f);
        highlightSprite->SetEnabled(highlight);
        mHighlighted = highlight;
    }

    void Tower::SetTargetType(const TowerTargetType &type)
    {
	    mTargetType = type;
    }

    const TowerTargetType& Tower::GetTargetType() const { return mTargetType; }

    void Tower::OnUpdate(float deltaTime)
    {
	    if(!mPlaced)
        {
            UpdateNonPlacedTower(deltaTime);
            return;
        }

	    switch(mTargetType)
        {
            case TowerTargetType::TARGET_CLOSEST_ENEMY:
                UpdateClosestEnemy(deltaTime);
                break;
            case TowerTargetType::TARGET_FARTHEST_ENEMY:
                UpdateFarthestEnemy(deltaTime);
                break;
            case TowerTargetType::TARGET_FARTHEST_ALONG_TRACK:
                UpdateFarthestEnemyAlongTrack(deltaTime);
                break;
            case TowerTargetType::TARGET_STRONGEST:
                UpdateStrongestEnemy(deltaTime);
                break;
        }
        UpdatePlacedTower(deltaTime);
    }

    void Tower::UpdateClosestEnemy(float deltaTime)
    {
	    if(ShouldUpdateTarget())
        {
            mTarget = mEnemyManager->GetClosestEnemy(
                    mTransform.GetWorldPosition(), GetRange());
        }
    }

    void Tower::UpdateFarthestEnemy(float deltaTime)
    {
	    if(ShouldUpdateTarget())
        {
            mTarget = mEnemyManager->GetFarthestEnemy(
                    mTransform.GetWorldPosition(), GetRange());
        }
    }

    void Tower::UpdateFarthestEnemyAlongTrack(float deltaTime)
    {
        if(ShouldUpdateTarget())
        {
            mTarget = mEnemyManager->GetFarthestEnemyAlongTrack(
                    mTransform.GetWorldPosition(), GetRange());
        }
    }

    void Tower::UpdateStrongestEnemy(float deltaTime)
    {
	    if(ShouldUpdateTarget())
        {
	        mTarget = mEnemyManager->GetStrongestEnemy(
	                mTransform.GetWorldPosition(), GetRange());
        }
    }

    bool Tower::ShouldUpdateTarget() const
    {
	    if(mTarget == nullptr)
        {
	        return true;
        }

	    // Prevents exception.
	    if(!mEnemyManager->ContainsEnemy(mTarget))
        {
	        return true;
        }

	    float distance = Vector2::Distance(
	            mTransform.GetWorldPosition(),
	            mTarget->GetTransform().GetWorldPosition());
	    return distance > GetRange();
    }

    bool Tower::IsPlaced() const { return mPlaced; }

    void Tower::PlaceTower()
    {
	    mScaleSelectAnimationComponent->SetEnabled(true);
	    mPlaced = true;
    }

	const std::string& Tower::GetName() const { return mName; }

	const TowerType& Tower::GetType() const { return mTowerType; }

	void Tower::OnSizeChanged(const Vector2& vec)
	{
		mCollisionComponent->SetSize(vec);
	}

	CollisionComponent* Tower::GetCollisionComponent() const { return mCollisionComponent; }

	Tower* Tower::CreateTowerFromType(class Game *game, const TowerType &towerType)
    {
	    switch(towerType)
        {
            case TowerType::GREEN_CANNON_TOWER_TYPE:
                return new GreenCannonTower(game);
        }
        return nullptr;
    }
}