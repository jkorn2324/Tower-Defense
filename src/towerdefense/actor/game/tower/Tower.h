#pragma once

#include "Actor.h"
#include "Vector2.h"

namespace TowerDefense
{


	class Tower : public Actor
	{

	public:
		Tower(class Game* game);

	private:
		void OnSizeChanged(const Vector2& vec);

	private:
		class TileSpriteComponent* mSpriteComponent;
		class CollisionComponent* mCollisionComponent;
	};
}