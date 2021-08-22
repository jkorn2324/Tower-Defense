//
// Created by jkorn on 8/15/2021.
//

#include "BuildingUI.h"

#include "Game.h"
#include "BuildingUISelectButton.h"
#include "Actor.h"
#include "GameUIActor.h"

#include "UIImageComponent.h"
#include "GameRenderer.h"

#include <SDL2/SDL.h>

namespace TowerDefense
{

    BuildingUI::BuildingUI(class Game *game)
            : GameUI(game)
    {
        InitializeButtons();
    }

    BuildingUI::BuildingUI(class Game *game, const Vector2 &uiSize)
            : GameUI(game, uiSize)
    {
        InitializeButtons();
    }

    void BuildingUI::InitializeButtons()
    {
        // Generates the green cannon tower.
        BuildingUISelectButton* greenCannonTower = new BuildingUISelectButton(this);
        greenCannonTower->SetTowerIconAndType("Assets/Icons/Green_Cannon.png",
                                                      TowerType::GREEN_CANNON_TOWER_TYPE);
        Vector2 buttonSize = greenCannonTower->GetButtonSize();
        buttonSize.y *= -1;
        Vector2 iconScreenPosition = GetScaledVector2(
                1.0f, 0.0f) - buttonSize;
        Vector2 iconWorldPosition = mGame->GetRenderer()
                ->ScreenToWorldPoint(iconScreenPosition);
        Transform& transform = (Transform&)greenCannonTower->GetTransform();
        transform.SetPosition(iconWorldPosition);
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