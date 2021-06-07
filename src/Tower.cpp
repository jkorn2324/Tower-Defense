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

		mSpriteComponent = new TileSpriteComponent(0, this,
			std::bind(&Tower::OnSizeChanged, this, std::placeholders::_1));
	}

	Tower::~Tower()
	{
	}

	void Tower::OnSizeChanged(const Vector2& vec)
	{
		mCollisionComponent->SetSize(vec);
	}
}