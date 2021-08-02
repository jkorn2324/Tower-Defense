#pragma once

#include <string>
#include <rapidjson/document.h>
#include <vector>
#include <unordered_map>
#include <functional>

#include "EventCallback.h"

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


    enum LevelWaveState
    {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_FINISHED
    };

    class LevelWaveActorDespawnObserver : public GenericEventObserverCallback<class Actor*>
    {
    public:
        explicit LevelWaveActorDespawnObserver(class Actor* actor);
    };

    /**
     * The level wave data.
     */
    class LevelWave
    {
    public:
        LevelWave(class Level* level, unsigned int waveID);
        ~LevelWave();

    public:
        void Start();
        void Update(float deltaTime);

    public:
        void SetNext(LevelWave* wave);
        bool HasNext() const;
        LevelWave* GetNext() const;

    public:
        void SetWaveFinishedCallback(std::function<void(class LevelWave*)> func);

    public:
        class Level* GetLevel() const;
        unsigned int GetWaveID() const;
        LevelWaveState GetState() const;

    private:
        void SpawnEnemy(const WaveEnemyData& enemyData);
        void OnEnemyDespawn(class Actor* enemy);
        void BeginWave();
        void FinishWave();

    private:
        // TODO: Callback function for enemy death
        // TODO: Callback function for ending wave
        unsigned int mWaveID;
        float mCurrentTime;
        LevelWave* mNext;
        unsigned int mCurrentEnemiesActive;
        unsigned int mEnemiesActive;
        class Level* mLevel;
        std::vector<WaveEnemyData> mWaveEnemyData;

    private:
        LevelWaveState mState;
        GenericEventCallback<class LevelWave*> mLevelWaveFinished;
        std::unordered_map<class Actor*, class LevelWaveActorDespawnObserver*> mActorDespawnedObservers;

    public:
        static LevelWave* Load(unsigned int waveID, class Level* level, const rapidjson::Document& document);
    };

#pragma endregion
}