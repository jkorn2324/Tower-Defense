#include "Camera.h"

namespace TowerDefense
{
    Camera::Camera(float sizeX, float sizeY)
    {
        mPosition = Vector2::Zero();
        mSize = Vector2(sizeX, sizeY);
    }

    void Camera::SetSize(float x, float y)
    {
        mSize.x = x;
        mSize.y = y;
    }

    void Camera::SetSize(const Vector2 &size)
    {
        mSize = size;
    }

    void Camera::SetPosition(float x, float y)
    {
        mPosition.x = x;
        mPosition.y = y;
    }

    void Camera::SetPosition(const Vector2 &position)
    {
        mPosition = position;
    }

    const Vector2& Camera::GetPosition() const
    {
        return mPosition;
    }

    Matrix4 Camera::GetOrthoMatrix() const
    {
        Matrix4 viewProjection = Matrix4::CreateSimpleViewProjection(mSize.x, mSize.y);
        Matrix4 position = Matrix4::CreatePosition(mPosition.x, mPosition.y, 0.0f);
        return viewProjection * position;
    }
}