#pragma once

#include "Vector2.h"
#include "Matrix4.h"

namespace TowerDefense
{

	/**
	 * Represents a 2D Transform. 
	 */
	class Transform
	{
	public:
		Transform();

	public:
		const Vector2& GetPosition() const;
		void SetPosition(const Vector2& position);
		void SetPosition(float x, float y);

	public:
		void LookAt(const Vector2& position);
		void MovePosition(const Vector2& position);

	public:
		const Vector2& GetScale() const;
		void SetScale(float scale);
		void SetScale(float x, float y);
		void SetScale(const Vector2& scale);

	public:
		Matrix4 CreateTransformMatrix();

	public:
		void SetRotation(float rotation, bool inRadians = false);
		float GetRotation() const;

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;

	};
}