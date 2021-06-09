#include "Level.h"
#include "LevelManager.h"
#include "JSONHelper.h"
#include "Actor.h"
#include "EnvironmentTile.h"
#include "GameParameters.h"

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
	}

	const std::string& Level::GetName() const
	{
		return mName;
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

		if(document.HasMember("layers"))
        {
		    float halfTileWidth = (float)tileWidth * 0.5f;
		    float halfTileHeight = (float)tileHeight * 0.5f;

		    Vector2 calculatedInitialPosition;
		    calculatedInitialPosition.x = -((float)levelWidth * 0.5f) * (float)tileWidth + halfTileWidth;
		    calculatedInitialPosition.y = (float)levelHeight * 0.5f * (float)tileHeight - halfTileHeight;

		    const auto& layers = document["layers"];
		    for(const auto& layer : layers.GetArray())
            {
                const auto& layerData = layer.GetObject();
                if(layerData.HasMember("data"))
                {
                    unsigned int currentIndex = 0;
                    const auto& data = layerData["data"].GetArray();
                    for(const auto& index : data)
                    {
                        unsigned int tileIndex = index.GetInt();
                        if(tileIndex == 0)
                        {
                            continue;
                        }
                        float extraXPos = (float)(currentIndex % levelWidth) * (float)tileWidth;
                        float extraYPos = (float)(currentIndex / levelWidth) * (float)tileHeight;
                        LevelTileData* tileData = new LevelTileData();
                        tileData->position = calculatedInitialPosition + Vector2(extraXPos, -extraYPos);
                        tileData->tileIndex = tileIndex - 1;
                        tileData->tileSizeX = tileWidth;
                        tileData->tileSizeY = tileHeight;
                        mTiles.push_back(tileData);
                        currentIndex++;
                    }
                    continue;
                }

                if(layerData.HasMember("objects")
                    && layerData.HasMember("Path-Nodes"))
                {
                    const auto& objects = layerData["objects"].GetArray();
                    for(const auto& node : objects)
                    {
                        const auto& nodeData = node.GetObject();
                        float xPosition = nodeData["x"].GetFloat();
                        float yPosition = nodeData["y"].GetFloat();

                        LevelPathNodeData* pathNodeData = new LevelPathNodeData();
                        pathNodeData->position = Vector2(xPosition, yPosition) + calculatedInitialPosition;
                        pathNodeData->next = nullptr;

                        if(mBeginPathNode == nullptr)
                        {
                            mBeginPathNode = pathNodeData;
                            continue;
                        }
                        mBeginPathNode->next = pathNodeData;
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
}