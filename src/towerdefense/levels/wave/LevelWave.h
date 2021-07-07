#pragma once

#include <string>
#include <rapidjson/document.h>
#include <vector>

namespace TowerDefense
{

#pragma region wave_enemy_data

    /**
     * The Wave enemy data.
     */
    struct WaveEnemyData
    {
        // Enemy Type Casted to enumerator.
        unsigned int enemyType;
        float beginSpawnTime;
        float spawnTimeDifference;
        int numSpawned;
        // TODO: enum for enemy type
    };

#pragma endregion

#pragma region level_wave

    /**
     * The level wave data.
     */
    class LevelWave
    {
    public:
        LevelWave(class Level* level, unsigned int waveID);

    public:
        void Start();
        void Update(float deltaTime);

    public:
        void SetNext(LevelWave* wave);
        bool HasNext() const;
        LevelWave* GetNext() const;

    public:
        class Level* GetLevel() const;
        unsigned int GetWaveID() const;

    private:
        void SpawnEnemy(const WaveEnemyData& enemyData);

    private:
        // TODO: Callback function for enemy death
        // TODO: Callback function for ending wave
        unsigned int mWaveID;
        float mCurrentTime;
        bool mStarted;
        LevelWave* mNext;
        class Level* mLevel;
        std::vector<WaveEnemyData> mWaveEnemyData;

    public:
        static LevelWave* Load(unsigned int waveID, class Level* level, const rapidjson::Document& document);
    };

#pragma endregion
}