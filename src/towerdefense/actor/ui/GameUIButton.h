//
// Created by jkorn on 8/8/2021.
//

#pragma once

#include "GameUIActor.h"

namespace TowerDefense
{
    class GameUIButton : public GameUIActor
    {
    public:
        GameUIButton(class GameUI* gameUI);

    public:
        bool IsWithinActor(const Vector2& position) const override;
        Vector2 GetButtonSize() const;

    protected:
        void OnUpdate(float deltaTime) override;

    protected:
        void OnMouseDown(const struct MouseButtonEventData& eventData) override;
        void OnMouseUp(const struct MouseButtonEventData& eventData) override;
        void OnMouseMove(const struct MouseMoveEventData& eventData) override;

    protected:
        virtual void OnMouseDownOnButton(const struct MouseButtonEventData& eventData)=0;
        virtual void OnMouseUpOnButton(const struct MouseButtonEventData& eventData, bool clickedSuccessfully)=0;
        virtual void OnMouseEnterButton(const struct MouseMoveEventData& eventData)=0;
        virtual void OnMouseExitButton(const struct MouseMoveEventData& eventData)=0;

    protected:
        class UIImageComponent* mImageComponent;
        class RectComponent* mRectComponent;

    private:
        bool mContainsMouse, mMouseHeld;

        float mMouseHeldTime;
        float mMaxMouseHeldTime;
    };
}