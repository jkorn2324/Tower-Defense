#include "Matrix3.h"
#include <cmath>
#include <memory>

namespace TowerDefense
{

	Matrix3::Matrix3() { }

	Matrix3::Matrix3(float mat[3][3])
	{
		std::memcpy(mMatrix, mat, 9 * sizeof(float));
	}

	const float* Matrix3::FloatPointer() const
	{
		return reinterpret_cast<const float*>(&mMatrix[0][0]);
	}

	Matrix3 Matrix3::CreateScale(float x, float y)
	{
		float mat[3][3] =
		{
			{x, 0.0f, 0.0f},
			{0.0f, y, 0.0f},
			{0.0f, 0.0f, 1.0f}
		};
		return Matrix3(mat);
	}

	Matrix3 Matrix3::CreatePosition(float x, float y)
	{
		float mat[3][3] =
		{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{x, y, 1.0f}
		};
		return Matrix3(mat);
	}

	Matrix3 Matrix3::CreateRotation(float rotation)
	{
		float mat[3][3] =
		{
			{std::cosf(rotation), std::sinf(rotation), 0.0f},
			{-std::sinf(rotation), std::cosf(rotation), 0.0f},
			{0.0f, 0.0f, 1.0f}
		};
		return Matrix3(mat);
	}

	Matrix3 operator*(const Matrix3& a, const Matrix3& b)
	{
		Matrix3 output;
		for (unsigned int outRow = 0; outRow < 3; outRow++)
		{
			for (unsigned int outCol = 0; outCol < 3; outCol++)
			{
				float outputValue = 0.0f;
				for (unsigned int column = 0; column < 3; column++)
				{
					outputValue += a.mMatrix[outRow][column] * b.mMatrix[column][outCol];
				}
				output.mMatrix[outRow][outCol] = outputValue;
			}
		}
		return output;
	}

	Matrix3& Matrix3::operator*=(const Matrix3& mat)
	{
		*this = *this * mat;
		return *this;
	}
}