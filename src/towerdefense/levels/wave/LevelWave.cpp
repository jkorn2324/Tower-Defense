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
        mStarted = false;
        mNext = nullptr;
        mWaveEnemyData = std::vector<WaveEnemyData>();
    }

    Level* LevelWave::GetLevel() const { return mLevel; }

    bool LevelWave::HasNext() const { return mNext != nullptr; }

    void LevelWave::SetNext(LevelWave *wave) { mNext = wave; }

    LevelWave* LevelWave::GetNext() const { return mNext; }

    unsigned int LevelWave::GetWaveID() const { return mWaveID; }

    void LevelWave::Start()
    {
        if(mStarted)
        {
            return;
        }
        // TODO: Implementation
        mStarted = true;
    }

    void LevelWave::Update(float deltaTime)
    {
        if(mStarted)
        {
            mCurrentTime += deltaTime;

            std::size_t enemyDataSize = mWaveEnemyData.size();
            if(enemyDataSize <= 0)
            {
                return;
            }

            SDL_Log("Update Enemy Data");

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
        // TODO: Implementation
    }

    void LevelWave::SpawnEnemy(const WaveEnemyData &enemyData)
    {
        switch(static_cast<EnemyType>(enemyData.enemyType))
        {
            case EnemyType::GREEN_ENEMY:
                new GreenEnemy(mLevel->GetGame());
                break;
        }

        SDL_Log("Spawning Enemy: %i", enemyData.enemyType);
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
