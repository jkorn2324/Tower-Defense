//
// Created by jkorn on 6/27/2021.
//

#include "LevelWave.h"

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
        // TODO: Implementation
    }

    LevelWave* LevelWave::Load(unsigned int waveID, const rapidjson::Document& document)
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
        const auto& waveDataAtIndex =  object[waveID].GetObject();
        // TODO: Load
        return nullptr;
    }
}
