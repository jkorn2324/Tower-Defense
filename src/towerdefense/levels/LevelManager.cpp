#include "LevelManager.h"
#include "Game.h"
#include "Level.h"
#include "GameParameters.h"

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
	    Level* level01 = new Level("Level1", "Assets/Levels/level1.json", this);
	    if(!level01->Load())
        {
	        return false;
        }
        SetActiveLevel("Level1");
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

    void LevelManager::SetActiveLevel(const std::string &levelName)
    {
	    const auto& searched = mLevels.find(levelName);
	    if(searched != mLevels.end())
        {
	        if(mActiveLevel != nullptr)
            {
                mActiveLevel->OnSetActive(false);
            }
	        mActiveLevel = (*searched).second;
	        mActiveLevel->OnSetActive(true);

	        if(DISPLAY_LOGS)
            {
                SDL_Log("Successfully set the active level: %s", levelName.c_str());
            }
	        return;
        }

	    if(DISPLAY_LOGS)
        {
            SDL_Log("Failed to find level: %s", levelName.c_str());
        }
    }
}