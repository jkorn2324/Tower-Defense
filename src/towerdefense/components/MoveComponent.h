#pragma once

#include "Component.h"
#include "Vector2.h"

namespace TowerDefense
{

    class MoveComponent : public Component
    {
    public:
        MoveComponent(class Actor* owner);

    public:
        void SetMovementSpeed(float movementSpeed);
        float GetMovementSpeed() const;
        void SetRotationSpeed(float rotationSpeed, bool inRadians = false);
        float GetRotationSpeed() const;

    public:
        virtual void Update(float deltaTime) override;

    private:
        float mMovementSpeed;
        float mRotationSpeed;
    };
}