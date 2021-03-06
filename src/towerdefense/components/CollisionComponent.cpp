#include "CollisionComponent.h"
#include "Actor.h"
#include "Transform.h"

#include <algorithm>

namespace TowerDefense
{

	CollisionComponent::CollisionComponent(Actor* actor)
		: RectComponent(actor) { }

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
		Vector2 offset;
		Vector2 otherMaxDiff = collisionComponent->GetMax() - GetMin();
		Vector2 otherMinDiff = collisionComponent->GetMin() - GetMax();
		Vector2 otherSize = collisionComponent->GetSize();

		std::vector<MinCollisionDiffData> minValues;
		AddMinimumValue(otherMinDiff.x, otherSize.x, CollisionSide::SIDE_RIGHT, minValues);
		AddMinimumValue(otherMaxDiff.x, otherSize.x, CollisionSide::SIDE_LEFT, minValues);
		AddMinimumValue(otherMinDiff.y, otherSize.y, CollisionSide::SIDE_BOTTOM, minValues);
		AddMinimumValue(otherMaxDiff.y, otherSize.y, CollisionSide::SIDE_TOP, minValues);

		if (minValues.size() <= 0)
		{
			data.mSide = CollisionSide::SIDE_NONE;
			data.mCollisionOffset = offset;
			return;
		}

		MinCollisionDiffData minimumAbsValue = *std::min_element(minValues.begin(), minValues.end(), 
			[](MinCollisionDiffData a, MinCollisionDiffData b) -> bool
			{
				return a.mAbsDiff < b.mAbsDiff;
			});
		
		if (minimumAbsValue.collisionSide == CollisionSide::SIDE_BOTTOM
			|| minimumAbsValue.collisionSide == CollisionSide::SIDE_TOP)
		{
			offset.y = minimumAbsValue.mDiff;
		}
		else
		{
			offset.x = minimumAbsValue.mDiff;
		}
		data.mSide = minimumAbsValue.collisionSide;
		data.mCollisionOffset = offset;
	}

	void CollisionComponent::AddMinimumValue(float value, float maxValue, CollisionSide side, std::vector<MinCollisionDiffData>& minValues)
	{
		float absValue = std::abs(value);
		if (absValue >= maxValue) 
		{ 
			return;
		}

		bool predicate = false;
		switch (side)
		{
		case CollisionSide::SIDE_RIGHT:
			predicate = value <= 0.0f;
			break;
		case CollisionSide::SIDE_LEFT:
			predicate = value >= 0.0f;
			break;
		case CollisionSide::SIDE_BOTTOM:
			predicate = value <= 0.0f;
			break;
		case CollisionSide::SIDE_TOP:
			predicate = value >= 0.0f;
			break;
		}

		if (predicate)
		{
			MinCollisionDiffData differenceData;
			differenceData.collisionSide = side;
			differenceData.mAbsDiff = absValue;
			differenceData.mDiff = value;
			minValues.push_back(differenceData);
		}
	}
}