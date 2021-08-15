#pragma once

#include <vector>

#include "RectComponent.h"
#include "Vector2.h"

namespace TowerDefense
{
	enum CollisionSide
	{
		SIDE_NONE,
		SIDE_TOP,
		SIDE_BOTTOM,
		SIDE_LEFT,
		SIDE_RIGHT
	};

	struct CollisionData
	{
		CollisionSide mSide;
		Vector2 mCollisionOffset;
	};

	struct MinCollisionDiffData
	{
		float mAbsDiff;
		float mDiff;
		CollisionSide collisionSide;
	};

	class CollisionComponent : public RectComponent
	{
	public:
		CollisionComponent(class Actor* owner);

	public:
		bool Intersects(CollisionComponent* other, CollisionData& collisionData);
		bool Intersects(class Actor* other, CollisionData& collisionData);

	private:
		void CalculateCollisionData(CollisionComponent* other, CollisionData& collisionData);
		void AddMinimumValue(float value, float maxValue, CollisionSide side, std::vector<MinCollisionDiffData>& minValues);
	};
}