#pragma once

#include "Actor.h"
#include "EventListener.h"

namespace TowerDefense
{

    class Player : public Actor
    {
    public:
        explicit Player(class Game* game);

    private:
        void OnMouseUp(const struct MouseButtonEventData& eventData);

    private:
        class MouseObserverComponent* mMouseObserverComponent;
    };
}