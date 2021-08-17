//
// Created by jkorn on 8/15/2021.
//

#include "BuildingUI.h"

#include "Game.h"
#include "BuildingUISelectButton.h"
#include "Actor.h"
#include "GameUIActor.h"

#include "UIImageComponent.h"

#include <SDL2/SDL.h>

namespace TowerDefense
{

    BuildingUI::BuildingUI(class Game *game)
            : GameUI(game)
    {
        InitializeButtons();
    }

    void BuildingUI::InitializeButtons()
    {
        BuildingUISelectButton* greenCannonTower = new BuildingUISelectButton(this);
        greenCannonTower->SetTowerIconAndType("Assets/Icons/Green_Cannon.png",
                                              TowerType::GREEN_CANNON_TOWER_TYPE);
        // TODO: Implementation
    }

    void BuildingUI::OnProcessInput(const Uint8 *keyState)
    {
        if(IsActive())
        {
            if(keyState[SDL_SCANCODE_ESCAPE])
            {
                SDL_Log("Processed Input");
            }
        }
    }
}