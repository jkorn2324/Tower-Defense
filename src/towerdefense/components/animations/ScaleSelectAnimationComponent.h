#pragma once

#include "Vector2.h"
#include "Component.h"

namespace TowerDefense
{

    /**
     * Scale selection component listens to when the mouse clicks on the object
     * and then changes the scale up and back down again.
     */
    class ScaleSelectAnimationComponent : public Component
    {
    public:
        ScaleSelectAnimationComponent(class Actor* owner);

    public:
        void SetTotalAnimationTime(float totalAnimationTime);
        float GetTotalAnimationTime() const;

    public:
        void SetMaxScale(const Vector2& maxScale);
        void SetMaxScale(float x, float y);
        const Vector2& GetMaxScale() const;

    public:
        void TriggerAnimation();
        virtual void Update(float deltaTime) override;

    private:
        float mCurrentAnimationTime;
        float mTotalAnimationTime;
        Vector2 mMaxScale;
        Vector2 mOriginalScale;
        Vector2 mCurrentScale;
    };
}