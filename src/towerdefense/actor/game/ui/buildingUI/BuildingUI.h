//
// Created by jkorn on 8/15/2021.
//

#pragma once

#include "GameUI.h"
#include "Vector2.h"

namespace TowerDefense
{

    class BuildingUI : public GameUI
    {
    public:
        explicit BuildingUI(class Game* game);
        BuildingUI(class Game* game, const Vector2& uiSize);

    protected:
        void OnProcessInput(const Uint8* keyState) override;

    private:
        void InitializeButtons();
    };
}
