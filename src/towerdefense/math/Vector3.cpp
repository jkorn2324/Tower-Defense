#include "Vector3.h"
#include "GameMath.h"

namespace TowerDefense
{
	
	Vector3::Vector3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->y = 0.0f;
	}

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3::Vector3(const Vector3& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}
	
	void Vector3::Normalize()
	{
		float length = Length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}

	const float* Vector3::FloatPointer() const
	{
		return reinterpret_cast<const float*>(&(this->x));
	}
	
	float Vector3::Length() const
	{
		return Sqrt(
			this->x * this->x + this->y * this->y + this->z * this->z);
	}
	
	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	
	Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 crossOutput;
		crossOutput.x = a.y * b.z - a.z * b.y;
		crossOutput.y = a.z * b.x - a.x * b.z;
		crossOutput.z = a.x * b.y - a.y * b.x;
		return crossOutput;
	}
	
	Vector3 Vector3::Normalize(const Vector3& vec)
	{
		float length = vec.Length();
		Vector3 newVec;
		newVec.x = vec.x / length;
		newVec.y = vec.y / length;
		newVec.z = vec.z / length;
		return newVec;
	}

	Vector3& Vector3::operator=(const Vector3& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		return *this;
	}

	Vector3& Vector3::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}
	
	bool operator==(const Vector3& a, const Vector3& b)
	{
		return a.x == b.x
			&& a.y == b.y
			&& a.z == b.z;
	}
	
	bool operator!=(const Vector3& a, const Vector3& b)
	{
		return a.x != b.x
			&& a.y != b.y
			&& a.z != b.z;
	}
	
	Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	
	Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	
	Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
	
	Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}
}