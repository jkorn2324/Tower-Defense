#include "Mouse.h"
#include <SDL2/SDL.h>

namespace TowerDefense
{

    Mouse::Mouse()
    {
        mDeltaPosition = Vector2();
        mPosition = Vector2();
        mHidden = false;
    }

    void Mouse::SetHidden(bool hidden)
    {
        if(mHidden != hidden)
        {
            SDL_ShowCursor(static_cast<int>(!hidden));
        }
        mHidden = hidden;
    }

    bool Mouse::IsHidden() const { return mHidden; }

    bool Mouse::Initialize()
    {
        SDL_GetRelativeMouseState(nullptr, nullptr);
        return true;
    }

    void Mouse::Update()
    {
        int newX, newY;
        SDL_GetRelativeMouseState(&newX, &newY);
        mDeltaPosition.x = static_cast<float>(newX);
        mDeltaPosition.y = -static_cast<float>(newY);
        mPosition += mDeltaPosition;
    }

    const Vector2& Mouse::GetMousePosition() const
    {
        return mPosition;
    }

    const Vector2& Mouse::GetDeltaPosition() const
    {
        return mDeltaPosition;
    }
}