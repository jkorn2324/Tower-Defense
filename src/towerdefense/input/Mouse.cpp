#include "Mouse.h"

#include "Game.h"
#include "GameRenderer.h"

#include <SDL2/SDL.h>

namespace TowerDefense
{

    Mouse::Mouse(Game* game)
    {
        mGame = game;
        mDeltaPosition = Vector2();
        mPosition = Vector2();
        mHidden = false;
        mListener = new GenericEventListener<MouseButtonEventData>();
    }

    Mouse::~Mouse()
    {
        delete mListener;
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

    void Mouse::OnMouseDown(SDL_MouseButtonEvent &button)
    {
        MouseButtonEventData eventData;
        eventData.mouseScreenPosition = Vector2(static_cast<float>(button.x),
                                          static_cast<float>(button.y));
        eventData.mouseWorldPosition = mGame->GetRenderer()->ScreenToWorldPoint(
                eventData.mouseScreenPosition);
        eventData.clickType = BUTTON_DOWN;

        switch(button.button)
        {
            case SDL_BUTTON_LEFT:
                eventData.buttonType = MouseButtonType::LEFT_CLICK;
                break;
            case SDL_BUTTON_RIGHT:
                eventData.buttonType = MouseButtonType::RIGHT_CLICK;
                break;
        }
        mListener->Invoke(eventData);
    }

    void Mouse::OnMouseUp(SDL_MouseButtonEvent &button)
    {
        MouseButtonEventData eventData;
        eventData.mouseScreenPosition = Vector2(static_cast<float>(button.x),
                                                static_cast<float>(button.y));
        eventData.mouseWorldPosition = mGame->GetRenderer()->ScreenToWorldPoint(
                eventData.mouseScreenPosition);
        eventData.clickType = BUTTON_UP;

        switch(button.button)
        {
            case SDL_BUTTON_LEFT:
                eventData.buttonType = MouseButtonType::LEFT_CLICK;
                break;
            case SDL_BUTTON_RIGHT:
                eventData.buttonType = MouseButtonType::RIGHT_CLICK;
                break;
        }
        mListener->Invoke(eventData);
    }

    GenericEventListener<MouseButtonEventData>* Mouse::GetListener() const
    {
        return mListener;
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