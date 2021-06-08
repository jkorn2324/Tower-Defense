#pragma once

#include <string>

namespace TowerDefense
{

	class Level
	{
	public:
		Level(const std::string& name, const std::string& levelPath, class LevelManager* mLevelManager);

	public:
		bool LoadLevel();

	public:
		const std::string& GetName() const;

	private:
		class LevelManager* mLevelManager;
		std::string mName;
		std::string mLevelPath;
	};
}