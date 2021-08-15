//
// Created by jkorn on 8/8/2021.
//

#include "GameUIButton.h"

#include "SpriteComponent.h"
#include "RectComponent.h"
#include "Mouse.h"

namespace TowerDefense
{

    GameUIButton::GameUIButton(class GameUI *gameUI)
            : GameUIActor(gameUI)
    {
        mContainsMouse = false;
        mMouseHeldTime = 0.0f;
        mMaxMouseHeldTime = 2.0f;
        mMouseHeld = false;
        mBackgroundSprite = new SpriteComponent(this);
        mRectComponent = new RectComponent(this);
    }

    void GameUIButton::OnUpdate(float deltaTime)
    {
        if(mMouseHeld)
        {
            mMouseHeldTime += deltaTime;
        }
    }

    void GameUIButton::OnMouseDown(const MouseButtonEventData &eventData)
    {
        if(mRectComponent->ContainsPosition(eventData.mouseWorldPosition)
            && mContainsMouse
            && eventData.buttonType == MouseButtonType::LEFT_CLICK)
        {
            SDL_Log("Mouse was pressed on button");
            // TODO: Mouse has been pressed
            mMouseHeld = true;
        }
    }

    void GameUIButton::OnMouseUp(const MouseButtonEventData& eventData)
    {
        if(mRectComponent->ContainsPosition(eventData.mouseWorldPosition)
            && mContainsMouse
            // Checks whether the mouse has been clicking on the button.
            && mMouseHeld
            && mMouseHeldTime > 0.0f && mMouseHeldTime <= mMaxMouseHeldTime)
        {
            SDL_Log("Mouse was raised on button.");
            // TODO: Mouse has been raised on button and clicked.
        }
        mMouseHeldTime = 0.0f;
        mMouseHeld = false;
    }

    void GameUIButton::OnMouseMove(const MouseMoveEventData &eventData)
    {
        if(mRectComponent->ContainsPosition(eventData.newMouseWorldPos)
            && !mContainsMouse)
        {
            SDL_Log("Mouse was moved onto button.");
            // TODO: Mouse has been moved onto button.
            mContainsMouse = true;
        }
        else if (!mRectComponent->ContainsPosition(eventData.newMouseWorldPos)
            && !mContainsMouse)
        {
            SDL_Log("Mouse was moved out of button.");
            // TODO: Mouse has moved out of button
            mContainsMouse = false;
        }
    }
}
