#pragma once

#include "Vector2.h"
#include "Matrix4.h"

namespace TowerDefense
{

    class Camera
    {
    public:
        Camera(float sizeX, float sizeY);

    public:
        void SetSize(float x, float y);
        void SetSize(const Vector2& size);
        const Vector2& GetSize() const;

    public:
        void SetPosition(float x, float y);
        void SetPosition(const Vector2& position);
        const Vector2& GetPosition() const;

    public:
        Matrix4 GetOrthoMatrix() const;

    private:
        Vector2 mSize;
        Vector2 mPosition;
    };
}