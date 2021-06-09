#pragma once

#include <string>
#include <unordered_map>

namespace TowerDefense
{

	class LevelManager
	{
	public:
		friend class Level;

	public:
		LevelManager(class Game* game);
		~LevelManager();

	public:
		Game* GetGame() const;
		class Level* GetActiveLevel() const;
		void SetActiveLevel(const std::string& levelName);

	public:
		bool InitLevels();

	private:
		void AddLevel(class Level* level);

	private:
		class Game* mGame;
		std::unordered_map<std::string, class Level*> mLevels;
		class Level* mActiveLevel;
	};
}