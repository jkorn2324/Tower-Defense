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
		SpriteComponent::SetTexture("Assets/Sprites/towerDefense_tilesheet.png");
		SetTileIndex(index);
	}

	TileSpriteComponent::TileSpriteComponent(unsigned int index, Actor* owner, std::function<void(const Vector2&)> func)
		: SpriteComponent(owner)
	{
		mTileIndex = 0;
		mTileSize = Vector2();
		SpriteComponent::SetTexture("Assets/Sprites/towerDefense_tilesheet.png");
		SetSizeChangedCallback(func);
		SetTileIndex(index);
	}

	TileSpriteComponent::~TileSpriteComponent() { }

	void TileSpriteComponent::SetTexture(Texture* texture)
	{
		SpriteComponent::SetTexture(texture);
		mTileSize.x = GetSize().x / static_cast<float>(TILES_PER_ROW);
		mTileSize.y = GetSize().y / static_cast<float>(TILES_PER_COLUMN);
	}

	void TileSpriteComponent::SetTileIndex(unsigned int index)
	{
		mTileIndex = index;
		Texture* texture = GetTexture();
		if (texture == nullptr)
		{
			return;
		}

		unsigned int col = index % TILES_PER_COLUMN;
		unsigned int row = index / TILES_PER_COLUMN;
		float xPos = static_cast<float>(row) * mTileSize.x + mTileSize.x * 0.5f;
		float yPos = static_cast<float>(col) * mTileSize.y + mTileSize.y * 0.5f;
		SetTexCoords(Vector2(xPos, yPos), mTileSize);
	}

	unsigned int TileSpriteComponent::GetTileIndex() const
	{
		return mTileIndex;
	}
}