#pragma once

#include <string>
#include <vector>

#include "Vector2.h"

namespace TowerDefense
{

	/**
	 * The Tile Data.
	 */
	struct LevelTileData
	{
	public:
	    unsigned int tileSizeX;
	    unsigned int tileSizeY;
		unsigned int tileIndex = 0;
		Vector2 position;
		bool colAsIndex = false;
	};

	/**
	 * The level path node data. 
	 */
	struct LevelPathNodeData
	{
		Vector2 position;
		LevelPathNodeData* next;
	};

	/**
	 * The Level Tile Data. 
	 */
	class Level
	{
	public:
		Level(const std::string& name, const std::string& levelPath, class LevelManager* mLevelManager);
		~Level();

	public:
	    bool Load();
		bool IsLoaded() const;
		class Game* GetGame() const;

	private:
		void OnSetActive(bool active);

	public:
		const std::string& GetName() const;

	private:
		class LevelManager* mLevelManager;
		std::string mName;
		std::string mLevelPath;
		bool mLoaded;

	private:
		LevelPathNodeData* mBeginPathNode;
		std::vector<LevelTileData*> mTiles;
	    std::vector<class Actor*> mActors;

	public:
	    friend class LevelManager;
    };
}