#pragma once

#include "Actor.h"

namespace TowerDefense
{


	class Tower : public Actor
	{

	public:
		Tower(class Game* game);
		virtual ~Tower();

	private:
		class SpriteComponent* mSpriteComponent;
	};
}