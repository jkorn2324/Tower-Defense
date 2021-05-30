#include "Tower.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "GameParameters.h"

namespace TowerDefense
{
	
	Tower::Tower(Game* game)
		: Actor(game)
	{
		mSpriteComponent = new SpriteComponent(
			"Assets/Sprites/towerDefense_tilesheet.png", this);

		SpriteTexCoords texCoords;
		texCoords.CreateTexCoords(
			Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), mSpriteComponent->GetTexture());
		mSpriteComponent->SetTexCoords(texCoords);
	}

	Tower::~Tower()
	{
		// TODO: Implementation
	}
}