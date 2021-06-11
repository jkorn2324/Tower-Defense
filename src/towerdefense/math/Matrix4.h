#pragma once


namespace TowerDefense
{

	class Matrix4
	{
	public:
		Matrix4();
		explicit Matrix4(float matrix[4][4]);

	public:
		const float* FloatPointer() const;

	public:
		friend Matrix4 operator*(const Matrix4& a, const Matrix4& b);
		friend Matrix4 operator+(const Matrix4& a, const Matrix4& b);
		friend Matrix4 operator-(const Matrix4& a, const Matrix4& b);
		Matrix4& operator+=(const Matrix4& other);
		Matrix4& operator-=(const Matrix4& other);
		Matrix4& operator*=(const Matrix4& other);

	public:
		static Matrix4 CreatePosition(float x, float y, float z);
		static Matrix4 CreateScale(float x, float y, float z);
		static Matrix4 CreateRotation2D(float rotation);

	public:
		static Matrix4 CreateSimpleViewProjection(float width, float height);
		static Matrix4 CreateOrthoViewProjection(float width, float height, float near, float far);

	public:
		static Matrix4 Identity();

	public:
		float mMatrix[4][4];
	};
}