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
		unsigned int layerIndex;
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
		unsigned int nodeIndex;
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
		LevelPathNodeData* GetFirstPathNode() const;
        const Vector2& GetLevelSize() const;
        bool CanPlaceTower(const Vector2& point) const;
        void Update(float deltaTime);

	private:
	    bool LoadLevelTiles();
	    bool LoadLevelWaves();
		void OnSetActive(bool active);

	public:
	    void AddActor(class Actor* actor);
	    void RemoveActor(class Actor* actor);

	public:
	    class LevelWave* GetCurrentWave() const;
	    class EnemyManager* GetEnemyManager() const;
	    class TowerManager* GetTowerManager() const;
	    class EnemyAffectorManager* GetEnemyAffectorManager() const;
		const std::string& GetName() const;

	private:
		class LevelManager* mLevelManager;
		class EnemyManager* mEnemyManager;
		class EnemyAffectorManager* mEnemyAffectorManager;
		class LevelTowersAreaManager* mTowerAreaManager;
		class TowerManager* mTowerManager;
		std::string mName;
		std::string mLevelPath;
		bool mLoaded;

	private:
	    class LevelWave* mFirstWave;
	    class LevelWave* mCurrentWave;

	private:
	    Vector2 mLevelSize;
		LevelPathNodeData* mBeginPathNode;
		std::vector<LevelTileData*> mTiles;
	    std::vector<class Actor*> mActors;

	public:
	    friend class LevelManager;
    };
}