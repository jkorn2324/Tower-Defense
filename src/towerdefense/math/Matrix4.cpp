#include "Matrix4.h"
#include "GameMath.h"
#include <memory>

namespace TowerDefense
{
	Matrix4::Matrix4() { }

	Matrix4::Matrix4(float matrix[4][4])
	{
		std::memcpy(mMatrix, matrix, 16 * sizeof(float));
	}

	const float* Matrix4::FloatPointer() const
	{
		return reinterpret_cast<const float*>(&mMatrix[0][0]);
	}
	
	Matrix4& Matrix4::operator*=(const Matrix4& other)
	{
		*this = *this * other;
		return *this;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& other)
	{
		*this = *this + other;
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4 &other)
	{
		*this = *this - other;
		return *this;
	}

	Matrix4 Matrix4::CreatePosition(float x, float y, float z)
	{
		float mat[4][4] =
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{x, y, z, 1.0f}
		};
		return Matrix4(mat);
	}
	
	Matrix4 Matrix4::CreateScale(float x, float y, float z)
	{
		float mat[4][4] =
		{
			{x, 0.0f, 0.0f, 0.0f},
			{0.0f, y, 0.0f, 0.0f},
			{0.0f, 0.0f, z, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
		return Matrix4(mat);
	}
	
	Matrix4 Matrix4::CreateRotation2D(float rotation)
	{
		float mat[4][4] =
		{
			{Cos(rotation), Sin(rotation), 0.0f, 0.0f},
			{-Sin(rotation), Cos(rotation), 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
		return Matrix4(mat);
	}

	Matrix4 Matrix4::CreateSimpleViewProjection(float width, float height)
	{
		float mat[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(mat);
	}

	Matrix4 Matrix4::CreateOrthoViewProjection(float width, float height, float near, float far)
	{
		float mat[4][4] =
		{
			{2.0f / width, 0.0f, 0.0f, 0.0f},
			{0.0f, 2.0f / height, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f / (far - near), 0.0f},
			{0.0f, 0.0f, near / (near - far), 1.0f}
		};
		return Matrix4(mat);
	}

	Matrix4 operator+(const Matrix4& a, const Matrix4& b)
	{
		unsigned int size = 4;
		Matrix4 output;

		for(unsigned int outRow = 0; outRow < size; outRow++)
		{
			for(unsigned int outCol = 0; outCol < size; outCol++)
			{
				output.mMatrix[outRow][outCol] = a.mMatrix[outRow][outCol]
						+ b.mMatrix[outRow][outCol];
			}
		}
		return output;
	}

	Matrix4 operator-(const Matrix4& a, const Matrix4& b)
	{
		unsigned int size = 4;
		Matrix4 output;

		for(unsigned int outRow = 0; outRow < size; outRow++)
		{
			for(unsigned int outCol = 0; outCol < size; outCol++)
			{
				output.mMatrix[outRow][outCol] = a.mMatrix[outRow][outCol]
												 - b.mMatrix[outRow][outCol];
			}
		}
		return output;
	}
	
	Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		unsigned int size = 4;
		Matrix4 output;
		for (unsigned int outRow = 0; outRow < size; outRow++)
		{
			for (unsigned int outCol = 0; outCol < size; outCol++)
			{
				float outputValue = 0.0f;
				for (unsigned int column = 0; column < size; column++)
				{
					outputValue += (a.mMatrix[outRow][column] * b.mMatrix[column][outCol]);
				}
				output.mMatrix[outRow][outCol] = outputValue;
			}
		}
		return output;
	}

	Matrix4 Matrix4::Identity()
	{
		float matrix[4][4] =
		{
			{1.0f, 0.0f, 0.0, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
		return Matrix4(matrix);
	}
}