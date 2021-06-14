#pragma once

#include "Tower.h"

namespace TowerDefense
{

    class GreenCannonTower : public Tower
    {
    public:
        GreenCannonTower(class Game* game);

    public:
        virtual float GetRange() const override;

    protected:
        virtual void UpdateNonPlacedTower(float deltaTime) override;
        virtual void UpdatePlacedTower(float deltaTime) override;
        virtual void OnDespawn() override;

    private:
        Actor* GenerateCannon();

    private:
        class Actor* mCannon;
    };
}