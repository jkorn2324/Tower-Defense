#pragma once

#include "Tower.h"

namespace TowerDefense
{

    const float GREEN_CANNON_ORIGINAL_RANGE = 300.0f;
    const float GREEN_CANNON_ORIGINAL_PROJECTILE_COOLDOWN = 0.8f;

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
        void UpdateProjectile(float deltaTime);
        void GenerateProjectile();

    private:
        float mRange;

        float mMaxProjectileCooldown;
        float mProjectileCooldown;

        class Actor* mCannon;
    };
}