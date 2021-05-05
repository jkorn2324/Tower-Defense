#include "TexturesManager.h"
#include "Game.h"
#include "Texture.h"

namespace TowerDefense
{

	TexturesManager::TexturesManager(Game* game)
	{
		mGame = game;
		mTextures = std::vector<Texture*>();
	}

	TexturesManager::~TexturesManager()
	{
		for(Texture* texture : mTextures)
		{
			delete texture;
		}
		mTextures.clear();
	}

	Game* TexturesManager::GetGame() const
	{
		return mGame;
	}

	Texture* TexturesManager::GetTexture(const std::string& fileName)
	{
		const auto& textureSearched = std::find_if(mTextures.begin(), mTextures.end(),
			[fileName](Texture* texture) -> bool
			{
				return texture->GetFileName() == fileName;
			});
		if (textureSearched != mTextures.end())
		{
			return *textureSearched;
		}

		Texture* texture = new Texture();
		if (!texture->Load(fileName))
		{
			delete texture;
			return nullptr;
		}
		mTextures.push_back(texture);
		return texture;
	}
}