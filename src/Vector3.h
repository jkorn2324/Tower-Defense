#pragma once

namespace TowerDefense
{


	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& vec);

	public:
		const float* FloatPointer() const;
		void Normalize();
		float Length() const;

	public:
		static float Dot(const Vector3& a, const Vector3& b);
		static Vector3 Cross(const Vector3& a, const Vector3& b);
		static Vector3 Normalize(const Vector3& vec);

	public:
		friend bool operator==(const Vector3& a, const Vector3& b);
		friend bool operator!=(const Vector3& a, const Vector3& b);

	public:
		friend Vector3 operator+(const Vector3& a, const Vector3& b);
		friend Vector3 operator-(const Vector3& a, const Vector3& b);
		friend Vector3 operator*(const Vector3& vec, float scalar);
		friend Vector3 operator*(const Vector3& a, const Vector3& b);

	public:
		Vector3& operator=(const Vector3& vec);
		Vector3& operator+=(const Vector3& vec);
		Vector3& operator-=(const Vector3& vec);
		Vector3& operator*=(const Vector3& vec);
		Vector3& operator*=(float scalar);

	public:
		float x;
		float y;
		float z;
	};
}