#pragma once

#include "Vector2.h"
#include "Matrix4.h"

namespace TowerDefense
{
	/**
	 * The Transform parent data. 
	 */
	struct TransformParentData
	{
		class Actor* parent = nullptr;
		bool useScale = true;
	};

	/**
	 * Represents a 2D Transform. 
	 */
	class Transform
	{
	public:
		friend class Actor;

	public:
		Transform();

	public:
		const Vector2& GetPosition() const;
		void SetPosition(const Vector2& position);
		void SetPosition(float x, float y);

	public:
		Vector2 GetWorldPosition() const;

	private:
		bool HasParent() const;
		void SetParent(class Actor* parent, bool useScale = false);

	public:
		void LookAt(const Vector2& position);
		void MovePosition(const Vector2& position);

	public:
		const Vector2& GetScale() const;
		void SetScale(float scale);
		void SetScale(float x, float y);
		void SetScale(const Vector2& scale);

	public:
		Matrix4 CreateTransformMatrix(bool useScale = true) const;

	public:
		void SetRotation(float rotation, bool inRadians = false);
		float GetRotation() const;
		Vector2 GetForward() const;

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;
		TransformParentData mParentData;
	};
}