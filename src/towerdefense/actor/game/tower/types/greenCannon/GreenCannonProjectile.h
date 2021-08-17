#pragma once

#include "TowerProjectile.h"
#include "EventCallback.h"

namespace TowerDefense
{

    const float GREEN_CANNON_PROJECTILE_SPEED = 700.0f;

    class GreenCannonProjectile : public TowerProjectile
    {
    public:
        explicit GreenCannonProjectile(class Game* game);
        ~GreenCannonProjectile();

    public:
        void SetTarget(class Actor* target);

    protected:
        void OnUpdate(float deltaTime) override;

    protected:
        virtual void OnEnemyCollision(const struct EnemyCollisionData& collisionData) override;

    private:
        void OnTargetDespawn(class Actor* actor);

    private:
        class Actor* mTarget;
        class TileSpriteComponent* mSpriteComponent;
        class ActorDespawnObserver* mDespawnObserver;
        bool mHitEnemy;
    };
}