#pragma once

#include "Vector2.h"
#include "Matrix3.h"

namespace TowerDefense
{

	class Transform
	{
	public:
		Transform();

	public:
		const Vector2& GetPosition() const;
		void SetPosition(const Vector2& position);
		void SetPosition(float x, float y);

	public:
		void MovePosition(const Vector2& position);

	public:
		const Vector2& GetScale() const;
		void SetScale(float scale);
		void SetScale(float x, float y);
		void SetScale(const Vector2& scale);

	public:
		void SetRotation(float rotation, bool inRadians = false);
		float GetRotation() const;

	public:
		Matrix3 GetTranslation() const;

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;
	};
}