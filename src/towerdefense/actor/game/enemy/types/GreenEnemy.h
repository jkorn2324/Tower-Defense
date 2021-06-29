#pragma once

#include "Enemy.h"

namespace TowerDefense
{
    const float GREEN_ENEMY_INITIAL_SPEED = 100.0f;

    class GreenEnemy : public Enemy
    {
    public:
        GreenEnemy(class Game* game);

    public:
        EnemyType GetEnemyType() const override;

    protected:
        void OnHealthChanged(const struct HealthChangedEventData& eventData) override;

    private:
        class TileSpriteComponent* mSpriteComponent;
    };
}