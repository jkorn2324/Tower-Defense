#pragma once

#include <string>
#include <vector>

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
		std::vector<class Texture*> mTextures;
		class Game* mGame;
	};
}