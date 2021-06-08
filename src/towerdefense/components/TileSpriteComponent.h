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
		TileSpriteComponent(unsigned int index, class Actor* owner);
		TileSpriteComponent(unsigned int index, class Actor* owner, std::function<void(const Vector2&)> func);
		virtual ~TileSpriteComponent();

	public:
		virtual void SetTexture(class Texture* texture) override;
		void SetTileIndex(unsigned int tileIndex);
		unsigned int GetTileIndex() const;

	public:
		void SetTilesData(unsigned int tilesPerCol, unsigned int tilesPerRow);
		void SetTilesData(const TilesData& tilesData);
		const TilesData& GetTilesData() const;
		
	private:
		unsigned int mTileIndex;
		Vector2 mTileSize;
		TilesData mTilesData;
	};
}