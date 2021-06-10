#pragma once

#include "Vector2.h"

namespace TowerDefense
{

    class Mouse
    {
    public:
        Mouse();

    public:
        bool Initialize();
        void Update();

    public:
        const Vector2& GetMousePosition() const;
        const Vector2& GetDeltaPosition() const;

    public:
        bool IsHidden() const;
        void SetHidden(bool hidden);

    private:
        bool mHidden;
        Vector2 mDeltaPosition;
        Vector2 mPosition;
    };
}