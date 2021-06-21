#pragma once

#include "TowerProjectile.h"

namespace TowerDefense
{

    const float GREEN_CANNON_PROJECTILE_SPEED = 700.0f;

    class GreenCannonProjectile : public TowerProjectile
    {
    public:
        GreenCannonProjectile(class Game* game);

    public:
        void SetTarget(class Actor* target);

    protected:
        void OnUpdate(float deltaTime) override;

    protected:
        virtual void OnEnemyCollision(const struct EnemyCollisionData& collisionData) override;

    private:
        class Actor* mTarget;
        class TileSpriteComponent* mSpriteComponent;
    };
}