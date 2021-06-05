#include "Transform.h"
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

	Matrix4 Transform::CreateTransformMatrix()
	{
		Matrix4 scaleMat = Matrix4::CreateScale(mScale.x, mScale.y, 1.0f);
		Matrix4 rotMat = Matrix4::CreateRotation2D(mRotation);
		Matrix4 posMat = Matrix4::CreatePosition(mPosition.x, mPosition.y, 0.0f);
		return scaleMat * rotMat * posMat;
	}
}