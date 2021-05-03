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

	Matrix3 Transform::GetTranslation() const
	{
		Matrix3 scale = Matrix3::CreateScale(mScale.x, mScale.y);
		Matrix3 rotation = Matrix3::CreateRotation(mRotation);
		Matrix3 position = Matrix3::CreatePosition(mPosition.x, mPosition.y);
		return scale * rotation * position;
	}
}