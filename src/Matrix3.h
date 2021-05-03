#pragma once

namespace TowerDefense
{

	class Matrix3
	{
	public:
		Matrix3();
		explicit Matrix3(float mat[3][3]);

	public:
		friend Matrix3 operator*(const Matrix3& a, const Matrix3& b);
		Matrix3& operator*=(const Matrix3& mat);

	public:
		static Matrix3 CreateScale(float x, float y);
		static Matrix3 CreatePosition(float x, float y);
		static Matrix3 CreateRotation(float rotation);

	public:
		float mMatrix[3][3];
	};
}