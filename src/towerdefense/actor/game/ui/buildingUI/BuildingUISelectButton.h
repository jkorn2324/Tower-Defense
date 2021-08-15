//
// Created by jkorn on 8/15/2021.
//

#pragma once

#include "GameUIButton.h"
#include "Tower.h"

#include <string>

namespace TowerDefense
{

    class BuildingUISelectButton : public GameUIButton
    {
    public:
        explicit BuildingUISelectButton(class BuildingUI* buildingUI);

    public:
        void SetTowerIconAndType(const std::string& towerIconPath, const TowerType& type);

    protected:
        void OnMouseDownOnButton(const struct MouseButtonEventData& eventData) override;
        void OnMouseUpOnButton(const struct MouseButtonEventData& eventData, bool clickedSuccessfully) override;
        void OnMouseEnterButton(const struct MouseMoveEventData& eventData) override;
        void OnMouseExitButton(const struct MouseMoveEventData& eventData) override;

    private:
        class ScaleSelectAnimationComponent* mScaleSelectAnimationComponent;

    private:
        TowerType mTowerType;
        class Player* mPlayer;
    };
}