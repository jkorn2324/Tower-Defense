//
// Created by jkorn on 6/28/2021.
//

#include "ScaleSelectAnimationComponent.h"
#include "Actor.h"
#include "Transform.h"
#include "GameMath.h"

namespace TowerDefense
{

    ScaleSelectAnimationComponent::ScaleSelectAnimationComponent(class Actor *owner)
            : Component(owner)
    {
        mOriginalScale = mTransform->GetScale();
        mCurrentScale = mOriginalScale;
        mMaxScale = mOriginalScale;
        mCurrentAnimationTime = 0.0f;
        mTotalAnimationTime = 0.0f;
    }

    void ScaleSelectAnimationComponent::SetMaxScale(const Vector2 &maxScale)
    {
        SetMaxScale(maxScale.x, maxScale.y);
    }

    void ScaleSelectAnimationComponent::SetMaxScale(float x, float y)
    {
        mMaxScale.x = x;
        mMaxScale.y = y;
    }

    const Vector2& ScaleSelectAnimationComponent::GetMaxScale() const { return mMaxScale; }

    void ScaleSelectAnimationComponent::SetTotalAnimationTime(float totalAnimationTime)
    {
        mTotalAnimationTime = totalAnimationTime;
    }

    float ScaleSelectAnimationComponent::GetTotalAnimationTime() const { return mTotalAnimationTime; }

    void ScaleSelectAnimationComponent::TriggerAnimation()
    {
        if(mTotalAnimationTime > 0.0f)
        {
            mTransform->SetScale(mOriginalScale);
            mCurrentAnimationTime = mTotalAnimationTime;
        }
    }

    void ScaleSelectAnimationComponent::Update(float deltaTime)
    {
        if(mCurrentAnimationTime > 0.0f)
        {
            mCurrentAnimationTime -= deltaTime;

            if(mCurrentAnimationTime <= deltaTime)
            {
                mCurrentScale = mOriginalScale;
                mTransform->SetScale(mCurrentScale);
                mCurrentAnimationTime = 0.0f;
                return;
            }

            float halfTime = mTotalAnimationTime * 0.5f;
            if(mCurrentAnimationTime < halfTime)
            {
                mCurrentScale = Lerp(
                        mOriginalScale, mMaxScale,
                        mCurrentAnimationTime / halfTime);
            }
            else
            {
                mCurrentScale = Lerp(
                        mMaxScale, mOriginalScale,
                        (mCurrentAnimationTime - halfTime) / halfTime);
            }
            mTransform->SetScale(mCurrentScale);
        }
    }
}
