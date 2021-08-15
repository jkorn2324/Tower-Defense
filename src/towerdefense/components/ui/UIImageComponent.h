//
// Created by jkorn on 8/15/2021.
//

#pragma once

#include "Component.h"
#include "Color.h"

#include <string>

namespace TowerDefense
{

    class UIImageComponent : public Component
    {
    public:
        UIImageComponent(class GameUIActor* owner);

    public:
        virtual void SetTexture(class Texture* texture);
        virtual void SetTexture(const std::string& file);

    public:
        void SetColorMultiplier(const Color& colorMultiplier);
        const Color& GetColorMultiplier() const;

    public:
        void Draw();

    private:
        Color mColorMultiplier;
    };
}
