//
// Created by jkorn on 8/14/2021.
//

#include "RectComponent.h"

#include "Transform.h"

namespace TowerDefense
{

    RectComponent::RectComponent(class Actor *owner)
            : Component(owner)
    {
        mSize = Vector2::One();
    }

    void RectComponent::SetSize(float x, float y)
    {
        mSize.x = x;
        mSize.y = y;
    }

    void RectComponent::SetSize(const Vector2 &size)
    {
        SetSize(size.x, size.y);
    }

    const Vector2& RectComponent::GetSize() const { return mSize; }

    bool RectComponent::ContainsPosition(const Vector2 &position) const
    {
        Vector2 min = GetMin();
        Vector2 max = GetMax();
        return min.x <= position.x && max.x >= position.x
               && min.y <= position.y && max.y >= position.y;
    }

    Vector2 RectComponent::GetMax() const
    {
        Vector2 scale = mTransform->GetScale();
        Vector2 transformPosition = mTransform->GetPosition();
        transformPosition.x += (mSize.x * 0.5f) * scale.x;
        transformPosition.y += (mSize.y * 0.5f) * scale.y;
        return transformPosition;
    }

    Vector2 RectComponent::GetMin() const
    {
        Vector2 scale = mTransform->GetScale();
        Vector2 transformPosition = mTransform->GetPosition();
        transformPosition.x -= (mSize.x * 0.5f) * scale.x;
        transformPosition.y -= (mSize.y * 0.5f) * scale.y;
        return transformPosition;
    }
}