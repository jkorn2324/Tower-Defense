//
// Created by jkorn on 6/28/2021.
//

#include "GreenEnemy.h"
#include "Game.h"
#include "GameParameters.h"

#include "EnemyAIComponent.h"
#include "HealthComponent.h"
#include "TileSpriteComponent.h"

namespace TowerDefense
{

    GreenEnemy::GreenEnemy(Game *game)
            : Enemy(game)
    {
        mEnemyAIComponent->SetMovementSpeed(
                GREEN_ENEMY_INITIAL_SPEED);

        mSpriteComponent = new TileSpriteComponent(this);
        ((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
        mSpriteComponent->SetTileSize(static_cast<float>(TILE_SIZE_X),
                                      static_cast<float>(TILE_SIZE_Y));
        mSpriteComponent->SetTileIndex(245);
    }

    EnemyType GreenEnemy::GetEnemyType() const
    {
        return EnemyType::GREEN_ENEMY;
    }

    void GreenEnemy::OnHealthChanged(const HealthChangedEventData &eventData)
    {
        Enemy::OnHealthChanged(eventData);
    }
}