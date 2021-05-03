#include "Vector2.h"
#include <cmath>

namespace TowerDefense
{
	Vector2::Vector2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2(const Vector2& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
	}

	void Vector2::Normalize()
	{
		float len = Length();
		this->x /= len;
		this->y /= len;
	}

	float Vector2::Length() const
	{
		return std::sqrtf(
			this->x * this->x + this->y * this->y);
	}

	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	
	Vector2 Vector2::Normalize(const Vector2& vec)
	{
		float len = vec.Length();
		Vector2 normalized(vec);
		normalized.x /= len;
		normalized.y /= len;
		return normalized;
	}

	Vector2 Vector2::Zero() { return Vector2(0.0f, 0.0f); }

	Vector2 Vector2::One() { return Vector2(1.0f, 1.0f); }

	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		Vector2 directionVector = b - a;
		return directionVector.Length();
	}

	Vector2 operator*(const Vector2& vec, float scalar)
	{
		Vector2 vector(vec);
		vector.x *= scalar;
		vector.y *= scalar;
		return vector;
	}

	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		Vector2 vector;
		vector.x = a.x * b.x;
		vector.y = a.y * b.y;
		return vector;
	}

	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		Vector2 vector;
		vector.x = a.x + b.x;
		vector.y = a.y + b.y;
		return vector;
	}

	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		Vector2 vector;
		vector.x = a.x - b.x;
		vector.y = a.y - b.y;
		return vector;
	}
	
	bool operator==(const Vector2& a, const Vector2& b)
	{
		return a.x == b.x 
			&& a.y == b.y;
	}
	
	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return a.x != b.x
			|| a.y != b.y;
	}

	Vector2& Vector2::operator=(const Vector2& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}
}