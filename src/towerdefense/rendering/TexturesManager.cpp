#include "TexturesManager.h"
#include "Game.h"
#include "Texture.h"

namespace TowerDefense
{

	TexturesManager::TexturesManager(Game* game)
	{
		mGame = game;
		mTextures = std::unordered_map<std::string, Texture*>();
	}

	TexturesManager::~TexturesManager()
	{
		for(const auto& texturePair : mTextures)
		{
		    Texture* texture = texturePair.second;
			texture->UnLoad();
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
	    const auto& textureSearched = mTextures.find(fileName);
		if (textureSearched != mTextures.end())
		{
			return (*textureSearched).second;
		}
		Texture* texture = new Texture();
		if (!texture->Load(fileName))
		{
			delete texture;
			return nullptr;
		}
		mTextures.emplace(fileName, texture);
		return texture;
	}
}