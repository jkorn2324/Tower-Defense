#pragma once

#include "CollisionComponent.h"
#include "EventCallback.h"

#include <functional>

namespace TowerDefense
{

    /**
     * The collision data.
     */
    struct EnemyCollisionData
    {
        class Enemy* enemy;
        CollisionData collisionData;
    };

    /**
     * An enemy affector component is a collision component
     * that only is triggered when it collides with enemies.
     */
    class EnemyAffectorComponent : public CollisionComponent
    {
    public:
        EnemyAffectorComponent(class Actor* owner);
        ~EnemyAffectorComponent();

    public:
        void SetEnemyCollisionCallback(std::function<void(const EnemyCollisionData&)> callback);
        void OnCollision(class Enemy* enemy, const CollisionData& collisionData);

    private:
        class Level* mLevel;
        EventCallback<const EnemyCollisionData&> mEnemyCollisionCallback;
    };
}
