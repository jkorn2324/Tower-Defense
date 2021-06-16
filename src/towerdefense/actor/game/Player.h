#pragma once

#include "Actor.h"
#include "EventListener.h"

namespace TowerDefense
{

    class Player : public Actor
    {
    public:
        explicit Player(class Game* game);

    public:
        void SetTowerSelected(class Tower* tower);

    protected:
        virtual void OnUpdate(float deltaTime) override;

    private:
        void SetTowerHighlighted(class Tower* tower);

    private:
        void UpdatePlacedTower(float deltaTime);
        void OnMouseUp(const struct MouseButtonEventData& eventData);
        void OnMouseDown(const struct MouseButtonEventData& eventData);

    private:
        class MouseObserverComponent* mMouseObserverComponent;
        class Tower* mPlacedTower;
        class Tower* mHighlightedTower;
    };
}