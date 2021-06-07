#include "LevelManager.h"
#include "Game.h"
#include "Level.h"

namespace TowerDefense
{
	LevelManager::LevelManager(Game* game)
	{
		mLevels = std::unordered_map<std::string, Level*>();
		mActiveLevel = nullptr;
		mGame = game;
	}

	LevelManager::~LevelManager()
	{
		for(const auto& levelPair : mLevels)
		{
			Level* level = levelPair.second;
			delete level;
		}
		mLevels.clear();
	}

	bool LevelManager::InitLevels()
	{
		// TODO: Implementation
		return true;
	}

	void LevelManager::AddLevel(Level* level)
	{
		mLevels.emplace(level->GetName(), level);
	}

	Game* LevelManager::GetGame() const
	{
		return mGame;
	}
	
	Level* LevelManager::GetActiveLevel() const
	{
		return mActiveLevel;
	}
}