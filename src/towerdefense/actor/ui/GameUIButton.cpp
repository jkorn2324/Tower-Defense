//
// Created by jkorn on 8/8/2021.
//

#include "GameUIButton.h"

#include "UIImageComponent.h"
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
        mImageComponent = new UIImageComponent(this);
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
            mMouseHeld = true;
            OnMouseDownOnButton(eventData);
        }
    }

    void GameUIButton::OnMouseUp(const MouseButtonEventData& eventData)
    {
        if(mRectComponent->ContainsPosition(eventData.mouseWorldPosition)
            && mContainsMouse)
        {
            // Checks whether the mouse has been clicking on the button
            bool clickedSuccessfully = mMouseHeld
               && mMouseHeldTime > 0.0f && mMouseHeldTime <= mMaxMouseHeldTime;
            OnMouseUpOnButton(eventData, clickedSuccessfully);
        }
        mMouseHeldTime = 0.0f;
        mMouseHeld = false;
    }

    void GameUIButton::OnMouseMove(const MouseMoveEventData &eventData)
    {
        if(mRectComponent->ContainsPosition(eventData.newMouseWorldPos)
            && !mContainsMouse)
        {
            mContainsMouse = true;
            OnMouseEnterButton(eventData);
        }
        else if (!mRectComponent->ContainsPosition(eventData.newMouseWorldPos)
            && !mContainsMouse)
        {
            mContainsMouse = false;
            OnMouseExitButton(eventData);
        }
    }
}
