#pragma once

#include <string>
#include <unordered_map>

namespace TowerDefense
{

	class TexturesManager
	{

	public:
		TexturesManager(class Game* game);
		~TexturesManager();

	public:
		class Game* GetGame() const;
		class Texture* GetTexture(const std::string& fileName);

	private:
	    std::unordered_map<std::string, class Texture*> mTextures;
		class Game* mGame;
	};
}