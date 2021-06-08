#include "Level.h"
#include "LevelManager.h"

namespace TowerDefense
{

	Level::Level(const std::string& levelName, const std::string& levelPath, LevelManager* manager)
	{
		mLevelPath = levelPath;
		mName = levelName;
		mLevelManager = manager;

		mLevelManager->AddLevel(this);
	}

	const std::string& Level::GetName() const
	{
		return mName;
	}

	bool Level::LoadLevel()
	{
		// TODO: Implementation
		return true;
	}
}