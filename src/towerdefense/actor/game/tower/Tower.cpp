#include "Tower.h"
#include "Game.h"
#include "TileSpriteComponent.h"
#include "Texture.h"
#include "GameParameters.h"
#include "CollisionComponent.h"
#include "LevelManager.h"
#include "TowerManager.h"
#include "Level.h"

#include <functional>

namespace TowerDefense
{
	
	Tower::Tower(Game* game)
		: Actor(game)
	{
		mCollisionComponent = new CollisionComponent(this);
		mCollisionComponent->SetSize(1.0f, 1.0f);

		mPlaced = false;
		mLevel = game->GetLevelManager()->GetActiveLevel();
        mName = DEFAULT_TOWER;
		mSpriteComponent = new TileSpriteComponent(this,
			std::bind(&Tower::OnSizeChanged, this, std::placeholders::_1));
		((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
		mSpriteComponent->SetTileSize(TILE_SIZE_X, TILE_SIZE_Y);
		mSpriteComponent->SetTileIndex(130);

		mLevel->GetTowerManager()->AddTower(this);
	}

    Tower::~Tower()
    {
        mLevel->GetTowerManager()->RemoveTower(this);
    }

    bool Tower::IsPlaced() const { return mPlaced; }

    void Tower::PlaceTower()
    {
	    mPlaced = true;
    }

	const std::string& Tower::GetName() const { return mName; }

	void Tower::OnSizeChanged(const Vector2& vec)
	{
		mCollisionComponent->SetSize(vec);
	}

	CollisionComponent* Tower::GetCollisionComponent() const { return mCollisionComponent; }
}