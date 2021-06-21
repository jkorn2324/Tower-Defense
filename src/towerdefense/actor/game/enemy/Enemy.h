#pragma once

#include "Actor.h"

namespace TowerDefense
{

    class Enemy : public Actor
    {
    public:
        Enemy(class Game* game);
        virtual ~Enemy();

    public:
        struct LevelPathNodeData* GetTargetPathNode() const;

    protected:
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnHealthChanged(const struct HealthChangedEventData& eventData);

    private:
        void OnSizeChanged(const Vector2& size);

    protected:
        class TileSpriteComponent* mSpriteComponent;
        class EnemyAIComponent* mEnemyAIComponent;
        class HealthComponent* mHealthComponent;

    private:
        class CollisionComponent* mCollisionComponent;
        class Level* mLevel;
    };
}