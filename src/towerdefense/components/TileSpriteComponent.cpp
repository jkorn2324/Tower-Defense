#include "TileSpriteComponent.h"
#include "Actor.h"
#include "Texture.h"

namespace TowerDefense
{

	TileSpriteComponent::TileSpriteComponent(unsigned int index, Actor* owner)
		: SpriteComponent(owner)
	{
		mTileIndex = 0;
		mTileSize = Vector2();
		mTilesData = TilesData();
		SetTileIndex(index);
	}

	TileSpriteComponent::TileSpriteComponent(unsigned int index, Actor* owner, std::function<void(const Vector2&)> func)
		: SpriteComponent(owner)
	{
		mTileIndex = 0;
		mTileSize = Vector2();
		mTilesData = TilesData();
		SetSizeChangedCallback(func);
		SetTileIndex(index);
	}

	TileSpriteComponent::~TileSpriteComponent() { }

	void TileSpriteComponent::SetTexture(Texture* texture)
	{
		SpriteComponent::SetTexture(texture);
		SetTilesData(1, 1);
	}

	void TileSpriteComponent::SetTileIndex(unsigned int index)
	{
		mTileIndex = index;
		Texture* texture = GetTexture();
		if (texture == nullptr)
		{
			return;
		}

		unsigned int col = index % mTilesData.mTilesPerColumn;
		unsigned int row = index / mTilesData.mTilesPerRow;
		float xPos = static_cast<float>(row) * mTileSize.x + mTileSize.x * 0.5f;
		float yPos = static_cast<float>(col) * mTileSize.y + mTileSize.y * 0.5f;
		SetTexCoords(Vector2(xPos, yPos), mTileSize);
	}

	unsigned int TileSpriteComponent::GetTileIndex() const
	{
		return mTileIndex;
	}

	void TileSpriteComponent::SetTilesData(unsigned int tilesPerCol, unsigned int tilesPerRow)
	{
		TilesData tilesData;
		tilesData.mTilesPerColumn = tilesPerCol;
		tilesData.mTilesPerRow = tilesPerRow;
		SetTilesData(tilesData);
	}
	
	void TileSpriteComponent::SetTilesData(const TilesData& tilesData)
	{
		Texture* currentTexture = GetTexture();
		if (currentTexture == nullptr)
		{
			return;
		}
		mTileSize.x = currentTexture->GetWidth() / static_cast<float>(tilesData.mTilesPerRow);
		mTileSize.y = currentTexture->GetHeight() / static_cast<float>(tilesData.mTilesPerColumn);
		mTilesData = tilesData;
		SetTileIndex(mTileIndex);
	}
	
	const TilesData& TileSpriteComponent::GetTilesData() const
	{
		return mTilesData;
	}
}