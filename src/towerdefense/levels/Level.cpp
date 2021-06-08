#include "Level.h"
#include "LevelManager.h"

namespace TowerDefense
{

	Level::Level(const std::string& levelName, const std::string& levelPath, LevelManager* manager)
	{
		mLevelPath = levelPath;
		mName = levelName;
		mLevelManager = manager;
        mLoaded = false;
		mLevelManager->AddLevel(this);
	}

	const std::string& Level::GetName() const
	{
		return mName;
	}

	bool Level::Load()
	{
		// TODO: Implementation
        if(mLoaded)
        {
            return true;
        }

		mLoaded = true;
		return true;
	}

    void Level::UnLoad()
    {
        if(!mLoaded)
        {
            return;
        }
        // TODO: Implementation
    }

    bool Level::IsLoaded() const
    {
        return mLoaded;
    }
}