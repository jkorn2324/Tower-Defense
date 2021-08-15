//
// Created by jkorn on 8/14/2021.
//

#pragma once

#include "Component.h"
#include "Vector2.h"

namespace TowerDefense
{

    class RectComponent : public Component
    {
    public:
        RectComponent(class Actor* owner);

    public:
        void SetSize(float x, float y);
        void SetSize(const Vector2& size);
        const Vector2& GetSize() const;

    public:
        Vector2 GetMin() const;
        Vector2 GetMax() const;

    public:
        bool ContainsPosition(const Vector2& position) const;

    protected:
        Vector2 mSize;
    };
}