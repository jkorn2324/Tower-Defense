#include "Level.h"
#include "LevelManager.h"
#include "JSONHelper.h"
#include "Actor.h"
#include "EnvironmentTile.h"
#include "GameParameters.h"

#include "Game.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "LevelTowerAreaRect.h"

#include <SDL2/SDL_log.h>
#include <rapidjson/document.h>


namespace TowerDefense
{

	Level::Level(const std::string& levelName, const std::string& levelPath, LevelManager* manager)
	{
		mLevelPath = levelPath;
		mName = levelName;
		mLevelManager = manager;
        mLoaded = false;
		mTiles = std::vector<LevelTileData*>();
		mBeginPathNode = nullptr;
		mEnemyManager = new EnemyManager(this);
		mTowerAreaManager = new LevelTowersAreaManager(this);
		mTowerManager = new TowerManager(this);
		mLevelSize = Vector2::Zero();
		mLevelManager->AddLevel(this);
	}

	Level::~Level()
	{
		for (const auto& tile : mTiles)
		{
			delete tile;
		}

		LevelPathNodeData* currentNodeData = mBeginPathNode;
		while(currentNodeData != nullptr)
        {
		    LevelPathNodeData* temp = currentNodeData->next;
		    delete currentNodeData;
		    currentNodeData = temp;
        }

		mBeginPathNode = nullptr;
		mTiles.clear();
		mActors.clear();

		// TODO: Save Towers

        delete mEnemyManager;
        delete mTowerAreaManager;
        delete mTowerManager;
    }

	const std::string& Level::GetName() const
	{
		return mName;
	}

	EnemyManager* Level::GetEnemyManager() const
    {
        return mEnemyManager;
    }

    TowerManager* Level::GetTowerManager() const
    {
	    return mTowerManager;
    }

	Game* Level::GetGame() const
	{
	    return mLevelManager->GetGame();
	}

	bool Level::Load()
	{
        if(mLoaded)
        {
            return true;
        }

		rapidjson::Document document;
		if (!ParseFile(mLevelPath, document))
		{
		    if(DISPLAY_LOGS)
            {
                SDL_Log("Unable to load level: %s", mName.c_str());
            }
			return false;
		}

		unsigned int levelWidth = static_cast<unsigned int>(document["width"].GetInt());
		unsigned int levelHeight = static_cast<unsigned int>(document["height"].GetInt());
		unsigned int tileHeight = static_cast<unsigned int>(document["tileheight"].GetInt());
		unsigned int tileWidth = static_cast<unsigned int>(document["tilewidth"].GetInt());

		mLevelSize.x = (float)levelWidth * (float)tileWidth;
        mLevelSize.y = (float)levelHeight * (float)tileHeight;

		if(document.HasMember("layers"))
        {
		    float halfTileWidth = (float)tileWidth * 0.5f;
		    float halfTileHeight = (float)tileHeight * 0.5f;

		    Vector2 calculatedInitialPosition;
		    calculatedInitialPosition.x = -((float)levelWidth * 0.5f) * (float)tileWidth;
		    calculatedInitialPosition.y = (float)levelHeight * 0.5f * (float)tileHeight;

		    unsigned int layerIndex = 0;
		    const auto& layers = document["layers"];
		    for(const auto& layer : layers.GetArray())
            {
                const auto& layerData = layer.GetObject();
                std::string layerType = layerData["type"].GetString();
                if(layerType == "tilelayer")
                {
                    unsigned int currentIndex = 0;
                    const auto& data = layerData["data"].GetArray();
                    for(const auto& index : data)
                    {
                        unsigned int tileIndex = index.GetInt();
                        if(tileIndex == 0)
                        {
                            currentIndex++;
                            continue;
                        }
                        float extraXPos = (float)(currentIndex % levelWidth) * (float)tileWidth;
                        float extraYPos = (float)(currentIndex / levelWidth) * (float)tileHeight;
                        LevelTileData* tileData = new LevelTileData();
                        tileData->layerIndex = layerIndex;
                        tileData->position = calculatedInitialPosition + Vector2(
                                extraXPos + halfTileWidth, -extraYPos - halfTileHeight);
                        tileData->tileIndex = tileIndex - 1;
                        tileData->tileSizeX = tileWidth;
                        tileData->tileSizeY = tileHeight;
                        mTiles.push_back(tileData);
                        currentIndex++;
                    }
                    layerIndex++;
                }
                else if (layerType == "objectgroup")
                {
                    const auto& objects = layerData["objects"].GetArray();
                    std::string layerName = layerData["name"].GetString();
                    if(layerName == "Path-Nodes")
                    {
                        LevelPathNodeData* prevPathNode = nullptr;
                        for(const auto& node : objects)
                        {
                            const auto& nodeData = node.GetObject();
                            float xPosition = nodeData["x"].GetFloat();
                            float yPosition = nodeData["y"].GetFloat();
                            Vector2 position = Vector2(xPosition, -yPosition) + calculatedInitialPosition;

                            std::string name = nodeData["name"].GetString();
                            if(name == "Enemy-Spawn-Position")
                            {
                                mEnemyManager->SetSpawnPosition(position);
                                continue;
                            }

                            LevelPathNodeData* pathNodeData = new LevelPathNodeData();
                            pathNodeData->position = position;
                            pathNodeData->next = nullptr;

                            if(prevPathNode == nullptr)
                            {
                                prevPathNode = pathNodeData;
                                mBeginPathNode = prevPathNode;
                                continue;
                            }

                            if(prevPathNode == mBeginPathNode)
                            {
                                prevPathNode->next = pathNodeData;
                                mBeginPathNode = prevPathNode;
                            }
                            else
                            {
                                prevPathNode->next = pathNodeData;
                            }
                            prevPathNode = pathNodeData;
                        }
                    }
                    else if (layerName == "Towers-Area")
                    {
                        for(const auto& object : objects)
                        {
                            const auto& objectData = object.GetObject();
                            Vector2 pos = Vector2(
                                    objectData["x"].GetFloat(),
                                    -objectData["y"].GetFloat());
                            Vector2 size = Vector2(
                                    objectData["width"].GetFloat(),
                                    objectData["height"].GetFloat());
                            mTowerAreaManager->AddTowerArea(size, pos + calculatedInitialPosition);
                        }
                    }
                }
            }
        }

		if(DISPLAY_LOGS)
        {
            SDL_Log("Successfully loaded the level: %s", mName.c_str());
        }
		mLoaded = true;
		return true;
	}

	LevelPathNodeData* Level::GetFirstPathNode() const
	{
	    return mBeginPathNode;
	}

	bool Level::CanPlaceTower(const Vector2 &point) const
    {
	    return mTowerAreaManager->CanPlaceTower(point)
	        && mTowerManager->CanPlaceTower(point);
    }

	void Level::OnSetActive(bool active)
	{
        if(active)
        {
            for(const auto& tile : mTiles)
            {
                EnvironmentTile* actorTile = new EnvironmentTile(tile, this);
                mActors.push_back(actorTile);
            }
            return;
        }
        mEnemyManager->ClearEnemies();
        mTowerManager->ClearTowers();
        for(const auto& actor : mActors)
        {
            actor->Despawn();
        }
        mActors.clear();
	}

    bool Level::IsLoaded() const
    {
        return mLoaded;
    }

    const Vector2& Level::GetLevelSize() const { return mLevelSize; }
}