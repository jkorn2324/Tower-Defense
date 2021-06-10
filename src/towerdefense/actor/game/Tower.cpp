#include "Tower.h"
#include "Game.h"
#include "TileSpriteComponent.h"
#include "Texture.h"
#include "GameParameters.h"
#include "CollisionComponent.h"

#include <functional>

namespace TowerDefense
{
	
	Tower::Tower(Game* game)
		: Actor(game)
	{
		mCollisionComponent = new CollisionComponent(this);
		mCollisionComponent->SetSize(1.0f, 1.0f);

		mSpriteComponent = new TileSpriteComponent(this,
			std::bind(&Tower::OnSizeChanged, this, std::placeholders::_1));
		((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
		mSpriteComponent->SetTilesPerColAndRow(TILE_SIZE_X, TILE_SIZE_Y);
		mSpriteComponent->SetTileIndex(130);
	}

	void Tower::OnSizeChanged(const Vector2& vec)
	{
		mCollisionComponent->SetSize(vec);
	}
}