#pragma once

#include "Actor.h"

namespace TowerDefense
{

    class TowerProjectile : public Actor
    {
    public:
        TowerProjectile(class Game* game);
        ~TowerProjectile();

    public:
        class Level* GetLevel() const;

    protected:
        virtual void OnEnemyCollision(const struct EnemyCollisionData& collisionData)=0;

    protected:
        class MoveComponent* mMoveComponent;
        class EnemyAffectorComponent* mEnemyAffectorComponent;
        class Level* mLevel;
    };
}