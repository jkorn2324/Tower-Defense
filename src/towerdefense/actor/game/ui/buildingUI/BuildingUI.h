//
// Created by jkorn on 8/15/2021.
//

#pragma once

#include "GameUI.h"

namespace TowerDefense
{

    class BuildingUI : public GameUI
    {
    public:
        explicit BuildingUI(class Game* game);

    protected:
        void OnProcessInput(const Uint8* keyState) override;

    private:
        void InitializeButtons();
    };
}
