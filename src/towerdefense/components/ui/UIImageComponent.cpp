//
// Created by jkorn on 8/15/2021.
//

#include "UIImageComponent.h"

namespace TowerDefense
{

    UIImageComponent::UIImageComponent(class GameUIActor *owner)
            : Component(reinterpret_cast<Actor*>(owner))
    {
        mColorMultiplier = Color::GetWhite();
    }

    void UIImageComponent::SetTexture(class Texture *texture)
    {
        // TODO: Implementation
    }

    void UIImageComponent::SetTexture(const std::string &file)
    {
        // TODO: Implementation
    }

    void UIImageComponent::SetColorMultiplier(const Color &colorMultiplier)
    {
        mColorMultiplier = colorMultiplier;
    }

    const Color& UIImageComponent::GetColorMultiplier() const { return mColorMultiplier; }

    void UIImageComponent::Draw()
    {
        // TODO: Implementation
    }
}
