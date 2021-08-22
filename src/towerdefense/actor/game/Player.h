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
        bool HasPlacedTower() const;
        void SetPlacedTower(class Tower* tower);

    protected:
        virtual void OnProcessInput(const Uint8* key) override;
        virtual void OnUpdate(float deltaTime) override;

    private:
        void SetTowerSelected(class Tower* tower);

    private:
        void UpdatePlacedTower(float deltaTime);
        void OnMouseUp(const struct MouseButtonEventData& eventData);
        void OnMouseDown(const struct MouseButtonEventData& eventData);

    private:
        class MouseObserverComponent* mMouseObserverComponent;
        class Tower* mPlacedTower;
        class Tower* mSelectedTower;
    };
}