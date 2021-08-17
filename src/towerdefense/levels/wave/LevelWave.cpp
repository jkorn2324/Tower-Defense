//
// Created by jkorn on 6/27/2021.
//

#include "LevelWave.h"
#include "Enemy.h"
#include "GreenEnemy.h"
#include "Level.h"
#include "Game.h"

#include <SDL2/SDL_log.h>

namespace TowerDefense
{

    LevelWave::LevelWave(class Level *level, unsigned int waveID)
    {
        mLevel = level;
        mWaveID = waveID;
        mCurrentTime = 0.0f;
        mState = LevelWaveState::STATE_IDLE;
        mNext = nullptr;
        mEnemiesActive = 0;
        mWaveEnemyData = std::vector<WaveEnemyData>();
        mActorDespawnedObservers = std::unordered_map<class Actor*, ActorDespawnObserver*>();
        mLevelWaveFinished = GenericEventCallback<LevelWave*>();
    }

    LevelWave::~LevelWave()
    {
        for(auto observerPair : mActorDespawnedObservers)
        {
            ActorDespawnObserver* observer = observerPair.second;
            delete observer;
        }
        mActorDespawnedObservers.clear();
    }

    Level* LevelWave::GetLevel() const { return mLevel; }

    bool LevelWave::HasNext() const { return mNext != nullptr; }

    void LevelWave::SetNext(LevelWave *wave) { mNext = wave; }

    LevelWave* LevelWave::GetNext() const { return mNext; }

    unsigned int LevelWave::GetWaveID() const { return mWaveID; }

    void LevelWave::SetWaveFinishedCallback(std::function<void(class LevelWave *)> func)
    {
        mLevelWaveFinished.SetCallback(func);
    }

    LevelWaveState LevelWave::GetState() const { return mState; }

    void LevelWave::Start()
    {
        if(mState != LevelWaveState::STATE_IDLE)
        {
            return;
        }

        if(mWaveEnemyData.empty())
        {
            FinishWave();
            return;
        }
        BeginWave();
    }

    void LevelWave::BeginWave()
    {
        // TODO: More Implementation
        mState = LevelWaveState::STATE_RUNNING;
    }

    void LevelWave::FinishWave()
    {
        if(mState == LevelWaveState::STATE_FINISHED)
        {
            return;
        }
        mState = LevelWaveState::STATE_FINISHED;
        mLevelWaveFinished.Invoke(this);
    }

    void LevelWave::Update(float deltaTime)
    {
        if(mState == LevelWaveState::STATE_RUNNING)
        {
            mCurrentTime += deltaTime;

            std::size_t enemyDataSize = mWaveEnemyData.size();
            if(enemyDataSize <= 0)
            {
                return;
            }

            // Loops through each and updates the enemy wave data.
            for(int i = enemyDataSize - 1; i >= 0; i--)
            {
                WaveEnemyData& waveData = mWaveEnemyData[i];
                if(mCurrentTime >= waveData.beginSpawnTime)
                {
                    SpawnEnemy(waveData);
                    waveData.beginSpawnTime = mCurrentTime
                            + waveData.spawnTimeDifference;
                    waveData.numSpawned--;

                    if(waveData.numSpawned < 0)
                    {
                        mWaveEnemyData.erase(
                                mWaveEnemyData.begin() + i);
                        continue;
                    }
                }
            }
        }
    }

    void LevelWave::SpawnEnemy(const WaveEnemyData &enemyData)
    {
        Enemy* enemy = nullptr;
        switch(static_cast<EnemyType>(enemyData.enemyType))
        {
            case EnemyType::GREEN_ENEMY:
                enemy = new GreenEnemy(mLevel->GetGame());
                break;
        }

        if(enemy != nullptr)
        {
            ActorDespawnObserver* despawnObserver =
                    new ActorDespawnObserver(enemy);
            despawnObserver->SetCallback(
                    std::bind(&LevelWave::OnEnemyDespawn, this, std::placeholders::_1));
            mActorDespawnedObservers.emplace(
                    enemy, despawnObserver);
        }
    }

    void LevelWave::OnEnemyDespawn(class Actor *enemy)
    {
        // Remove observers from enemy observer list.
        const auto& searchedIteratedEnemy =
                mActorDespawnedObservers.find(enemy);
        if(searchedIteratedEnemy != mActorDespawnedObservers.end())
        {
            ActorDespawnObserver* observer
                    = mActorDespawnedObservers[enemy];
            mActorDespawnedObservers.erase(searchedIteratedEnemy);
            delete observer;
        }

        if(mActorDespawnedObservers.empty()
            && mWaveEnemyData.empty())
        {
            FinishWave();
        }
    }

    LevelWave* LevelWave::Load(unsigned int waveID, Level* level, const rapidjson::Document& document)
    {
        if(!document.HasMember("wavesData"))
        {
            return nullptr;
        }
        const auto& object = document["wavesData"].GetArray();
        if(waveID >= object.Size())
        {
            return nullptr;
        }

        LevelWave* levelWave = new LevelWave(level, waveID);
        const auto& waveDataAtIndex =  object[waveID].GetObject();
        for(const auto& waveKeyData : waveDataAtIndex)
        {
            const auto& enemyDataObject = waveKeyData.value.GetObject();

            WaveEnemyData enemyData;
            enemyData.enemyType = (unsigned int)GetEnemyTypeFromLocalizedString(
                    enemyDataObject["enemy-type"].GetString());
            enemyData.beginSpawnTime = enemyDataObject["time-begin"].GetFloat();
            enemyData.numSpawned = enemyDataObject["spawn-amount"].GetInt();
            enemyData.spawnTimeDifference = enemyDataObject["time-difference"].GetFloat();
            levelWave->mWaveEnemyData.push_back(enemyData);
        }
        return levelWave;
    }
}
