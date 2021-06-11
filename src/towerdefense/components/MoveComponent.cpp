#include "MoveComponent.h"

#include "Transform.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

namespace TowerDefense
{

    MoveComponent::MoveComponent(class Actor* owner)
            : Component(owner)
    {
        mMovementSpeed = 0.0f;
        mRotationSpeed = 0.0f;
    }

    void MoveComponent::SetMovementSpeed(float movementSpeed) { mMovementSpeed = movementSpeed; }

    float MoveComponent::GetMovementSpeed() const { return mMovementSpeed; }

    void MoveComponent::SetRotationSpeed(float rotationSpeed, bool inRadians)
    {
        float deg2Rad = (float)M_PI / 180.0f;
        mRotationSpeed = inRadians ? rotationSpeed : deg2Rad * rotationSpeed;
    }

    float MoveComponent::GetRotationSpeed() const
    {
        return mRotationSpeed;
    }

    void MoveComponent::Update(float deltaTime)
    {
        // Updates the rotation.
        float mRotation = mTransform->GetRotation();
        mTransform->SetRotation(mRotation +
            mRotationSpeed * deltaTime, true);

        // Updates the position.
        Vector2 currentDirection = mTransform->GetForward();
        mTransform->MovePosition(currentDirection
            * deltaTime * mMovementSpeed);
    }
}