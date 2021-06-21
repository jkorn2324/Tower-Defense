#pragma once

#include <vector>

namespace TowerDefense
{
    class EnemyAffectorManager
    {
    public:
        EnemyAffectorManager(class Level* level);

    public:
        void Update(float deltaTime);

    private:
        void AddAffector(class EnemyAffectorComponent* affector);
        void RemoveAffector(class EnemyAffectorComponent* affector);

    private:
        std::vector<class EnemyAffectorComponent*> mAffectors;
        class EnemyManager* mEnemyManager;
        class Level* mLevel;

    public:
        friend class EnemyAffectorComponent;
    };
}