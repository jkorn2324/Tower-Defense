#pragma once

#include "Actor.h"

namespace TowerDefense
{

    class Enemy : public Actor
    {
    public:
        Enemy(class Game* game);
        virtual ~Enemy();

    protected:
        virtual void OnUpdate(float deltaTime) override;

    private:
        void OnSizeChanged(const Vector2& size);

    protected:
        class TileSpriteComponent* mSpriteComponent;
        class EnemyAIComponent* mEnemyAIComponent;

    private:
        class CollisionComponent* mCollisionComponent;
        class Level* mLevel;
    };
}