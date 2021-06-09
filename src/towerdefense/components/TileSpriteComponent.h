#pragma once

#include "SpriteComponent.h"

namespace TowerDefense
{

	struct TilesData
	{
	public:
		unsigned int mTilesPerColumn = 1;
		unsigned int mTilesPerRow = 1;
	};

	class TileSpriteComponent : public SpriteComponent
	{
	public:
		TileSpriteComponent(class Actor* owner);
		TileSpriteComponent(class Actor* owner, std::function<void(const Vector2&)> func);
		virtual ~TileSpriteComponent();

	public:
		virtual void SetTexture(class Texture* texture) override;
		void SetTileIndex(unsigned int tileIndex, bool colsAsIndex = false);
		unsigned int GetTileIndex() const;

	public:
		void SetTilesPerColAndRow(unsigned int tilesPerCol, unsigned int tilesPerRow);
		void SetTileSize(const Vector2& tileSize);
		void SetTileSize(float x, float y);
		const Vector2& GetTileSize() const;
		
	private:
		unsigned int mTileIndex;
		Vector2 mTileSize;
		TilesData mTilesData;
	};
}