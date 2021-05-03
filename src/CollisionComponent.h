#pragma once

#include "Component.h"
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

	class CollisionComponent : public Component
	{
	public:
		CollisionComponent(class Actor* owner);

	public:
		void SetSize(float x, float y);
		void SetSize(const Vector2& size);
		Vector2 GetMin() const;
		Vector2 GetMax() const;

	public:
		bool Intersects(CollisionComponent* other, CollisionData& collisionData);
		bool Intersects(class Actor* other, CollisionData& collisionData);

	private:
		void CalculateCollisionData(CollisionComponent* other, CollisionData& collisionData);

	private:
		Vector2 mColliderSize;
		class Transform* mTransform;

	};
}