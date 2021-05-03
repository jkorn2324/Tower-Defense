#include "CollisionComponent.h"
#include "Actor.h"
#include "Transform.h"

namespace TowerDefense
{

	CollisionComponent::CollisionComponent(Actor* actor)
		: Component(actor)
	{
		mColliderSize = Vector2::One();
		mTransform = (Transform*)&actor->GetTransform();
	}

	void CollisionComponent::SetSize(float x, float y)
	{
		mColliderSize.x = x;
		mColliderSize.y = y;
	}

	void CollisionComponent::SetSize(const Vector2& size)
	{
		mColliderSize = size;
	}

	Vector2 CollisionComponent::GetMin() const
	{
		Vector2 scale = mTransform->GetScale();
		Vector2 transformPosition = mTransform->GetPosition();
		transformPosition.x -= (mColliderSize.x * 0.5f) * scale.x;
		transformPosition.y -= (mColliderSize.y * 0.5f) * scale.y;
		return transformPosition;
	}

	Vector2 CollisionComponent::GetMax() const
	{
		Vector2 scale = mTransform->GetScale();
		Vector2 transformPosition = mTransform->GetPosition();
		transformPosition.x += (mColliderSize.x * 0.5f) * scale.x;
		transformPosition.y += (mColliderSize.y * 0.5f) * scale.y;
		return transformPosition;
	}

	bool CollisionComponent::Intersects(CollisionComponent* other, CollisionData& collisionData)
	{
		Vector2 otherMin = other->GetMin();
		Vector2 otherMax = other->GetMax();
		Vector2 thisMin = GetMin();
		Vector2 thisMax = GetMax();
		
		bool intersects = otherMin.x <= thisMax.x
			&& otherMin.y <= thisMax.y
			&& thisMin.x <= otherMax.x
			&& thisMin.y <= otherMax.y;

		if (!intersects)
		{
			collisionData.mCollisionOffset = Vector2::Zero();
			collisionData.mSide = CollisionSide::SIDE_NONE;
			return false;
		}

		CalculateCollisionData(other, collisionData);
		return true;
	}

	bool CollisionComponent::Intersects(Actor* other, CollisionData& collisionData)
	{
		if (other == nullptr)
		{
			return false;
		}
		CollisionComponent* otherCollisionComponent = other->GetComponent<CollisionComponent>();
		if (otherCollisionComponent == nullptr)
		{
			return false;
		}
		return Intersects(otherCollisionComponent, collisionData);
	}

	void CollisionComponent::CalculateCollisionData(CollisionComponent* collisionComponent, 
		CollisionData& data)
	{
		// TODO: Implementation
	}
}