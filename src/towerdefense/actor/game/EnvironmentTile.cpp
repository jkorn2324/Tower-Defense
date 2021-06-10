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
        mSpriteComponent->SetTileSize(static_cast<float>(tileData->tileSizeX),
                                      static_cast<float>(tileData->tileSizeY));
        mSpriteComponent->SetTileIndex(tileData->tileIndex, tileData->colAsIndex);
        ((SpriteComponent*)mSpriteComponent)->SetDrawLayer(tileData->layerIndex);

        mLevel = level;
        mTransform.SetPosition(tileData->position);
    }
}