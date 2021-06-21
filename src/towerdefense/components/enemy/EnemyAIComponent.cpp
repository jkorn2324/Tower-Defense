#include "EnemyAIComponent.h"

#include "Level.h"
#include "Transform.h"
#include "Vector2.h"

#include <cmath>

namespace TowerDefense
{

    EnemyAIComponent::EnemyAIComponent(Actor *owner, Level* level)
            : MoveComponent(owner)
    {
        mLevel = level;
        mCurrentPathNode = level->GetFirstPathNode();
        mTransform->LookAt(mCurrentPathNode->position);
        // TODO: Don't hard code.
        mMaximumDistanceToPathNode = 5.0f;
    }

    void EnemyAIComponent::SetMaximumDistanceToPathNode(float distance)
    {
        mMaximumDistanceToPathNode = distance;
    }

    float EnemyAIComponent::GetMaximumDistanceToPathNode() const { return mMaximumDistanceToPathNode; }

    /**
     * Gets the target path node. Returns null if the enemy has finished navigating the path.
     *
     * @return LevelPathNodeData* - The current path node the enemy is traversing towards.
     */
    LevelPathNodeData* EnemyAIComponent::GetTargetPathNode() const
    {
        return mCurrentPathNode;
    }

    void EnemyAIComponent::Update(float deltaTime)
    {
        UpdateAI(deltaTime);
        MoveComponent::Update(deltaTime);
    }

    void EnemyAIComponent::UpdateAI(float deltaTime)
    {
        if(mCurrentPathNode == nullptr)
        {
            return;
        }
        const Vector2& currentPosition = mTransform->GetPosition();
        float distanceToTarget = Vector2::Distance(
                currentPosition, mCurrentPathNode->position);

        if(distanceToTarget <= mMaximumDistanceToPathNode)
        {
            mCurrentPathNode = mCurrentPathNode->next;
            SetRotationSpeed(CalculateAngularSpeed(), true);
            return;
        }

        Vector2 directionToTarget = mCurrentPathNode->position - currentPosition;
        directionToTarget.Normalize();
        float dotProductTarget = Vector2::Dot(mTransform->GetForward(), directionToTarget);

        if(dotProductTarget >= 0.95f)
        {
            mTransform->LookAt(mCurrentPathNode->position);
            SetRotationSpeed(0.0f);
        }
        else if(dotProductTarget < 0.25f)
        {
            SetRotationSpeed(CalculateAngularSpeed(), true);
        }
    }

    float EnemyAIComponent::CalculateAngularSpeed() const
    {
        if(mCurrentPathNode == nullptr)
        {
            return 0.0f;
        }
        const Vector2& currentPosition = mTransform->GetWorldPosition();
        Vector2 newDirection = mCurrentPathNode->position - currentPosition;
        float newDistanceToTarget = newDirection.Length();
        newDirection.Normalize();
        float dotProduct = Vector2::Dot(mTransform->GetForward(), newDirection);
        if(dotProduct >= 0.95f)
        {
            return 0.0f;
        }
        float crossProduct = Vector2::Cross(mTransform->GetForward(), newDirection);
        float angleDifference = std::acosf(dotProduct);
        float timeToReachNewTarget = (newDistanceToTarget / GetMovementSpeed()) * 0.25f;
        float rotationSpeed = (angleDifference / timeToReachNewTarget) * 3.0f;
        return rotationSpeed * (crossProduct / std::abs(crossProduct));
    }
}