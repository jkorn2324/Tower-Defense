#pragma once

#include "Tower.h"

namespace TowerDefense
{

    const float GREEN_CANNON_ORIGINAL_RANGE = 300.0f;

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
        float mRange;
        class Actor* mCannon;
    };
}