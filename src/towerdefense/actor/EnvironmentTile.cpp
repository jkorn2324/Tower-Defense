#include "EnvironmentTile.h"
#include "Level.h"
#include "TileSpriteComponent.h"
#include "SpriteComponent.h"
#include "GameParameters.h"

namespace TowerDefense
{

    EnvironmentTile::EnvironmentTile(LevelTileData *tileData, Level *level)
        : Actor(level->GetGame())
    {
        mSpriteComponent = new TileSpriteComponent(this);
        ((SpriteComponent*)mSpriteComponent)->SetTexture(TILESHEET_PATH);
        mSpriteComponent->SetTileSize(tileData->tileSizeX, tileData->tileSizeY);
        mSpriteComponent->SetTileIndex(tileData->tileIndex, tileData->colAsIndex);

        mLevel = level;
        mTransform.SetPosition(tileData->position);
    }
}