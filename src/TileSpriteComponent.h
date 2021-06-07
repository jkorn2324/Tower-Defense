#pragma once

#include "SpriteComponent.h"

namespace TowerDefense
{

#pragma region constants

	const unsigned int TILES_PER_COLUMN = 13;
	const unsigned int TILES_PER_ROW = 23;

#pragma endregion

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

	private:
		unsigned int mTileIndex;
	
	private:
		Vector2 mTileSize;
	};
}