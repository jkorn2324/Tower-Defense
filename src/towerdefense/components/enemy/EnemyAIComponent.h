#pragma once

#include "MoveComponent.h"

namespace TowerDefense
{

    /**
     * The Enemy AI Movement Component.
     */
    class EnemyAIComponent : public MoveComponent
    {
    public:
        EnemyAIComponent(class Actor* owner, class Level* level);

    public:
        float GetMaximumDistanceToPathNode() const;
        void SetMaximumDistanceToPathNode(float distance);
        virtual void Update(float deltaTime) override;

    private:
        float CalculateAngularSpeed() const;
        void UpdateAI(float deltaTime);

    private:
        class Level* mLevel;
        struct LevelPathNodeData* mCurrentPathNode;
        float mMaximumDistanceToPathNode;
    };
}