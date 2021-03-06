#pragma once

#include <string>

namespace TowerDefense
{

	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& vec);

	public:
		const float* FloatPointer() const;
		std::string ToString() const;
		void Normalize();
		float Length() const;

	public:
		friend bool operator==(const Vector2& a, const Vector2& b);
		friend bool operator!=(const Vector2& a, const Vector2& b);
		friend Vector2 operator*(const Vector2& vec, float scalar);
		friend Vector2 operator*(const Vector2& a, const Vector2& b);
		friend Vector2 operator+(const Vector2& a, const Vector2& b);
		friend Vector2 operator-(const Vector2& a, const Vector2& b);

	public:
		Vector2& operator=(const Vector2& vec);
		Vector2& operator*=(float scalar);
		Vector2& operator*=(const Vector2& vec);
		Vector2& operator+=(const Vector2& vec);
		Vector2& operator-=(const Vector2& vec);

	public:
		static float Dot(const Vector2& a, const Vector2& b);
		static Vector2 Normalize(const Vector2& vec);
		static float Distance(const Vector2& a, const Vector2& b);
		static Vector2 Zero();
		static Vector2 One();
		static float Cross(const Vector2& a, const Vector2& b);

	public:
		float x;
		float y;
	};
}