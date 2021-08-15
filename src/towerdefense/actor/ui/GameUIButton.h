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

    protected:
        void OnUpdate(float deltaTime) override;

    protected:
        void OnMouseDown(const struct MouseButtonEventData& eventData) override;
        void OnMouseUp(const struct MouseButtonEventData& eventData) override;
        void OnMouseMove(const struct MouseMoveEventData& eventData) override;

    private:
        class SpriteComponent* mBackgroundSprite;
        class RectComponent* mRectComponent;

    private:
        float mMouseHeldTime;
        float mMaxMouseHeldTime;

        bool mContainsMouse, mMouseHeld;
    };
}