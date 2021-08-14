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
        mClickListener = new GenericEventListener<MouseButtonEventData>();
        mMoveListener = new GenericEventListener<MouseMoveEventData>();
    }

    Mouse::~Mouse()
    {
        delete mClickListener;
        delete mMoveListener;
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

    void Mouse::OnMouseMove(SDL_MouseMotionEvent &event)
    {
        MouseMoveEventData eventData;
        eventData.prevMouseScreenPos = mPosition;
        eventData.prevMouseWorldPos = mGame->GetRenderer()->ScreenToWorldPoint(
                eventData.prevMouseScreenPos);

        mDeltaPosition.x = static_cast<float>(event.xrel);
        mDeltaPosition.y = static_cast<float>(event.yrel);
        mPosition.x = static_cast<float>(event.x);
        mPosition.y = static_cast<float>(event.y);

        eventData.newMouseScreenPos = mPosition;
        eventData.newMouseWorldPos = mGame->GetRenderer()->ScreenToWorldPoint(
                eventData.newMouseScreenPos);
        mMoveListener->Invoke(eventData);
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
        mClickListener->Invoke(eventData);
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
        mClickListener->Invoke(eventData);
    }

    GenericEventListener<MouseButtonEventData>* Mouse::GetClickListener() const { return mClickListener; }

    GenericEventListener<MouseMoveEventData>* Mouse::GetMoveListener() const { return mMoveListener; }

    const Vector2& Mouse::GetMousePosition() const
    {
        return mPosition;
    }

    const Vector2& Mouse::GetDeltaPosition() const
    {
        return mDeltaPosition;
    }
}