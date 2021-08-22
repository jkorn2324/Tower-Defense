//
// Created by jkorn on 8/8/2021.
//

#pragma once

#include "Actor.h"

namespace TowerDefense
{

    class GameUIActor : public Actor
    {
    public:
        GameUIActor(class GameUI* ui);
        virtual ~GameUIActor();

    public:
        virtual bool IsWithinActor(const Vector2& position) const =0;

    protected:
        virtual void OnMouseDown(const struct MouseButtonEventData& eventData)=0;
        virtual void OnMouseUp(const struct MouseButtonEventData& eventData)=0;
        virtual void OnMouseMove(const struct MouseMoveEventData& eventData)=0;

    protected:
        class GameUI* mGameUI;
        class MouseObserverComponent* mMouseObserverComponent;
    };
}