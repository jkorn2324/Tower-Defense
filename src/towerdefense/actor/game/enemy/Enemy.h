#pragma once

#include <string>

#include "Actor.h"

namespace TowerDefense
{

#pragma region enemy_type

    // TODO: Implementation

    enum EnemyType
    {
        GREEN_ENEMY,
        UNKNOWN
    };

    EnemyType GetEnemyTypeFromLocalizedString(const std::string& name);

#pragma endregion

#pragma region enemy_class

    class Enemy : public Actor
    {
    public:
        Enemy(class Game* game);
        virtual ~Enemy();

    public:
        struct LevelPathNodeData* GetTargetPathNode() const;
        virtual EnemyType GetEnemyType() const =0;

    protected:
        virtual void OnHealthChanged(const struct HealthChangedEventData& eventData);

    protected:
        class EnemyAIComponent* mEnemyAIComponent;
        class HealthComponent* mHealthComponent;
        class CollisionComponent* mCollisionComponent;

    private:
        class Level* mLevel;
    };

#pragma endregion
}