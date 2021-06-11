#include "Transform.h"
#include "Actor.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

namespace TowerDefense
{
	Transform::Transform()
	{
		mScale = Vector2::One();
		mPosition = Vector2::Zero();
		mRotation = 0.0f;
	}

	const Vector2& Transform::GetPosition() const
	{
		return mPosition;
	}

	void Transform::LookAt(const Vector2& position)
	{
        Vector2 directionVector = position - mPosition;
		directionVector.Normalize();
		mRotation = std::atan2f(directionVector.y, directionVector.x);
	}

	void Transform::MovePosition(const Vector2& position)
	{
		mPosition += position;
	}
	
	void Transform::SetPosition(const Vector2& position)
	{
		mPosition = position;
	}
	
	void Transform::SetPosition(float x, float y)
	{
		mPosition.x = x;
		mPosition.y = y;
	}

	Vector2 Transform::GetWorldPosition() const
	{
		if (!HasParent())
		{
			return GetPosition();
		}
		const Transform& transform = mParentData.parent->GetTransform();
		return transform.GetWorldPosition() + GetPosition();
	}

	const Vector2& Transform::GetScale() const
	{
		return mScale;
	}
	
	void Transform::SetScale(float scale)
	{
		mScale.x = scale;
		mScale.y = scale;
	}
	
	void Transform::SetScale(float x, float y)
	{
		mScale.x = x;
		mScale.y = y;
	}
	
	void Transform::SetScale(const Vector2& scale)
	{
		mScale = scale;
	}

	float Transform::GetRotation() const
	{
		return mRotation;
	}

	void Transform::SetRotation(float rotation, bool inRadians)
	{
		float deg2Rad = (float)M_PI / 180.0f;
		mRotation = inRadians ? rotation : deg2Rad * rotation;
	}

	Vector2 Transform::GetForward() const
    {
	    float x = std::cosf(mRotation);
	    float y = std::sinf(mRotation);
	    Vector2 forwardDirection(x, y);
	    forwardDirection.Normalize();
	    return forwardDirection;
    }

	bool Transform::HasParent() const
	{
		return mParentData.parent != nullptr;
	}

	void Transform::SetParent(Actor* parent, bool useScale)
	{
		mParentData.parent = parent;
		mParentData.useScale = useScale;
	}

	Matrix4 Transform::CreateTransformMatrix(bool useScale) const
	{
		Matrix4 scaleMat = useScale ? Matrix4::CreateScale(
			mScale.x, mScale.y, 1.0f) : Matrix4::Identity();
		Matrix4 rotMat = Matrix4::CreateRotation2D(mRotation);
		Matrix4 posMat = Matrix4::CreatePosition(mPosition.x, mPosition.y, 0.0f);
		Matrix4 transformMatrix = scaleMat * rotMat * posMat;

		if (HasParent())
		{
			Transform& parentTransform = (Transform&)mParentData.parent->GetTransform();
			Matrix4 parentMatrix = parentTransform.CreateTransformMatrix(mParentData.useScale);
			transformMatrix *= parentMatrix;
		}
		return transformMatrix;
	}
}