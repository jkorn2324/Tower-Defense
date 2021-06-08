#pragma once

#include <string>
#include <vector>

namespace TowerDefense
{

	class Level
	{
	public:
		Level(const std::string& name, const std::string& levelPath, class LevelManager* mLevelManager);

	public:
	    bool Load();
	    void UnLoad();
	    bool IsLoaded() const;

	public:
		const std::string& GetName() const;

	private:
		class LevelManager* mLevelManager;
		std::string mName;
		std::string mLevelPath;
		bool mLoaded;

	private:
	    std::vector<class Actor*> mActors;
	};
}