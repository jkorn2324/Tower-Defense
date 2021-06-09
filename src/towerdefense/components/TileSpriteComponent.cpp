#include "TileSpriteComponent.h"
#include "Actor.h"
#include "Texture.h"

namespace TowerDefense
{

	TileSpriteComponent::TileSpriteComponent(Actor* owner)
		: SpriteComponent(owner)
	{
		mTileIndex = 0;
		mTileSize = Vector2();
		mTilesData = TilesData();
		SetTileIndex(0);
	}

	TileSpriteComponent::TileSpriteComponent(Actor* owner, std::function<void(const Vector2&)> func)
		: SpriteComponent(owner)
	{
		mTileIndex = 0;
		mTileSize = Vector2();
		mTilesData = TilesData();
		SetSizeChangedCallback(func);
		SetTileIndex(0);
	}

	TileSpriteComponent::~TileSpriteComponent() { }

	void TileSpriteComponent::SetTexture(Texture* texture)
	{
		SpriteComponent::SetTexture(texture);
		SetTilesPerColAndRow(1, 1);
	}

	void TileSpriteComponent::SetTileIndex(unsigned int index, bool colsAsIndex)
	{
		mTileIndex = index;
		Texture* texture = GetTexture();
		if (texture == nullptr)
		{
			return;
		}

		unsigned int col, row;
		if (colsAsIndex)
		{
			col = index % mTilesData.mTilesPerColumn;
			row = index / mTilesData.mTilesPerColumn;
		}
		else
		{
			col = index / mTilesData.mTilesPerRow;
			row = index % mTilesData.mTilesPerRow;
		}
		float xPos = static_cast<float>(row) * mTileSize.x + mTileSize.x * 0.5f;
		float yPos = static_cast<float>(col) * mTileSize.y + mTileSize.y * 0.5f;
		SetTexCoords(Vector2(xPos, yPos), mTileSize);
	}

	unsigned int TileSpriteComponent::GetTileIndex() const
	{
		return mTileIndex;
	}

	void TileSpriteComponent::SetTilesPerColAndRow(unsigned int tilesPerCol, unsigned int tilesPerRow)
	{
		Texture* currentTexture = GetTexture();
		if (currentTexture == nullptr)
		{
			return;
		}
		mTileSize.x = currentTexture->GetWidth() / static_cast<float>(tilesPerRow);
		mTileSize.y = currentTexture->GetHeight() / static_cast<float>(tilesPerCol);
		mTilesData.mTilesPerRow = tilesPerRow;
		mTilesData.mTilesPerColumn = tilesPerCol;
		SetTileIndex(mTileIndex);
	}

	void TileSpriteComponent::SetTileSize(const Vector2 &tileSize)
	{
		SetTileSize(tileSize.x, tileSize.y);
	}

	void TileSpriteComponent::SetTileSize(float x, float y)
	{
		Texture* texture = GetTexture();
		if(texture != nullptr)
		{
			mTilesData.mTilesPerRow = static_cast<unsigned int>(texture->GetWidth() / x);
			mTilesData.mTilesPerColumn = static_cast<unsigned int>(texture->GetHeight() / y);
		}
		mTileSize.x = x;
		mTileSize.y = y;
		SetTileIndex(mTileIndex);
	}

	const Vector2& TileSpriteComponent::GetTileSize() const
	{
		return mTileSize;
	}
}