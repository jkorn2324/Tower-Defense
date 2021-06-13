#pragma once

#include "Actor.h"
#include "Vector2.h"

#include <string>

#ifndef DEFAULT_TOWER
#define DEFAULT_TOWER "DefaultTower"
#endif

namespace TowerDefense
{


	class Tower : public Actor
	{

	public:
		explicit Tower(class Game* game);
		virtual ~Tower();

	public:
	    virtual void PlaceTower();
	    bool IsPlaced() const;

	public:
        const std::string& GetName() const;
        class CollisionComponent* GetCollisionComponent() const;

	private:
		void OnSizeChanged(const Vector2& vec);

	protected:
		class TileSpriteComponent* mSpriteComponent;
		class CollisionComponent* mCollisionComponent;

	private:
	    std::string mName;
	    class Level* mLevel;
	    bool mPlaced;
	};
}