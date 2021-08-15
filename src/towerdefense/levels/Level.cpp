#include "Level.h"
#include "LevelManager.h"
#include "JSONHelper.h"
#include "Actor.h"
#include "EnvironmentTile.h"
#include "GameParameters.h"

#include "Game.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemyAffectorManager.h"
#include "TowerManager.h"
#include "LevelTowerAreaRect.h"
#include "LevelWave.h"

#include <SDL2/SDL_log.h>
#include <rapidjson/document.h>


namespace TowerDefense
{

	Level::Level(const std::string& levelName, const std::string& levelPath, LevelManager* manager)
	{
		mLevelPath = levelPath;
		mName = levelName;
		mCurrentWave = nullptr;
		mFirstWave = nullptr;
		mLevelManager = manager;
        mLoaded = false;
		mTiles = std::vector<LevelTileData*>();
		mActors = std::vector<Actor*>();
		mBeginPathNode = nullptr;
		mEnemyManager = new EnemyManager(this);
		mTowerAreaManager = new LevelTowersAreaManager(this);
		mTowerManager = new TowerManager(this);
		mEnemyAffectorManager = new EnemyAffectorManager(this);
		mLevelSize = Vector2::Zero();
        mLevelWaveChangedListener =
                new GenericEventListener<const LevelWaveChangedEventData&>();
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

		LevelWave* currentWave = mFirstWave;
		while(currentWave != nullptr)
        {
		    LevelWave* temp = currentWave->GetNext();
		    delete currentWave;
		    currentWave = temp;
        }
        mFirstWave = mCurrentWave = nullptr;

		mTiles.clear();
		mActors.clear();

		// TODO: Save Towers

        delete mEnemyManager;
        delete mTowerAreaManager;
        delete mTowerManager;
        delete mEnemyAffectorManager;
        delete mLevelWaveChangedListener;
    }

    void Level::Update(float deltaTime)
    {
	    if(mCurrentWave != nullptr)
        {
	        // TODO: Remove Start - Only here for testing purposes
	        mCurrentWave->Start();
	        mCurrentWave->Update(deltaTime);
        }
	    mEnemyAffectorManager->Update(deltaTime);
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

    GenericEventListener<const LevelWaveChangedEventData&>* Level::GetLevelWaveChangedListener() const
    {
	    return mLevelWaveChangedListener;
    }

    EnemyAffectorManager* Level::GetEnemyAffectorManager() const { return mEnemyAffectorManager; }

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

		if(!LoadLevelTiles()
		    || !LoadLevelWaves())
        {
		    return false;
        }

		if(DISPLAY_LOGS)
        {
            SDL_Log("Successfully loaded the level: %s", mName.c_str());
        }

		mLoaded = true;
		return true;
	}

	bool Level::LoadLevelTiles()
    {
        rapidjson::Document document;
        if (!ParseFile(mLevelPath + "/tilesData.json", document))
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
                                pathNodeData->nodeIndex = 0;
                                prevPathNode = pathNodeData;
                                mBeginPathNode = prevPathNode;
                                continue;
                            }

                            if(prevPathNode == mBeginPathNode)
                            {
                                pathNodeData->nodeIndex = prevPathNode->nodeIndex + 1;
                                prevPathNode->next = pathNodeData;
                                mBeginPathNode = prevPathNode;
                            }
                            else
                            {
                                pathNodeData->nodeIndex = prevPathNode->nodeIndex + 1;
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
        return true;
    }

    bool Level::LoadLevelWaves()
    {
        rapidjson::Document document;
        if (!ParseFile(mLevelPath + "/wavesData.json", document))
        {
            if(DISPLAY_LOGS)
            {
                SDL_Log("Unable to load level: %s", mName.c_str());
            }
            return false;
        }

        unsigned int numWaves = document["waves"].GetUint();
        if(numWaves == 0)
        {
            return true;
        }

        unsigned int currentWaveID = 0;
        LevelWave* prevLevelWave = nullptr;
        while(currentWaveID < numWaves)
        {
            LevelWave* currentWave = LevelWave::Load(
                    currentWaveID, this, document);
            if(currentWave == nullptr)
            {
                currentWaveID++;
                continue;
            }

            if(prevLevelWave == nullptr)
            {
                prevLevelWave = currentWave;

                if(numWaves <= 1)
                {
                    mFirstWave = prevLevelWave;
                }
            }
            else
            {
                prevLevelWave->SetNext(currentWave);
                if(mFirstWave == nullptr)
                {
                    mFirstWave = prevLevelWave;
                }
            }
            currentWaveID++;
        }

        mCurrentWave = mFirstWave;

        if(mCurrentWave != nullptr)
        {
            mCurrentWave->SetWaveFinishedCallback(
                    std::bind(&Level::OnWaveFinished, this, std::placeholders::_1));
        }
	    return true;
    }

    void Level::OnWaveFinished(LevelWave *waveFinished)
    {
        waveFinished->SetWaveFinishedCallback(nullptr);

        LevelWaveChangedEventData eventData;
        eventData.prevWave = waveFinished;

        if(waveFinished->HasNext())
        {
            LevelWave* nextWave = (LevelWave*)waveFinished->GetNext();
            mCurrentWave = nextWave;
            mCurrentWave->SetWaveFinishedCallback(
                    std::bind(&Level::OnWaveFinished, this, std::placeholders::_1));

            eventData.nextWave = nextWave;
            mLevelWaveChangedListener->Invoke(eventData);
            return;
        }

        eventData.nextWave = nullptr;
        mLevelWaveChangedListener->Invoke(eventData);
        mCurrentWave = nullptr;
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

	void Level::AddActor(Actor *actor)
    {
	    const auto& searchedActor = std::find(
	            mActors.begin(), mActors.end(), actor);
	    if(searchedActor != mActors.end())
        {
            mActors.push_back(actor);
        }
    }

    void Level::RemoveActor(class Actor *actor)
    {
	    const auto& removedActor = std::find(
	            mActors.begin(), mActors.end(), actor);
	    mActors.erase(removedActor);
    }

    bool Level::IsLoaded() const
    {
        return mLoaded;
    }

    const Vector2& Level::GetLevelSize() const { return mLevelSize; }
}