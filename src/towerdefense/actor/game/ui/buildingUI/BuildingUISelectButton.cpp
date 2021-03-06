//
// Created by jkorn on 8/15/2021.
//

#include "BuildingUISelectButton.h"

#include "BuildingUI.h"
#include "Mouse.h"
#include "Game.h"
#include "ActorManager.h"
#include "Player.h"

#include "UIImageComponent.h"
#include "RectComponent.h"
#include "ScaleSelectAnimationComponent.h"

namespace TowerDefense
{

    BuildingUISelectButton::BuildingUISelectButton(class BuildingUI *buildingUI)
            : GameUIButton(buildingUI)
    {
        mTowerType = TowerType::DEFAULT_TOWER_TYPE;
        mPlayer = mGame->GetActorManager()->GetPlayer();
    }

    void BuildingUISelectButton::SetTowerIconAndType(const std::string &towerIconPath, const TowerType &type)
    {
        mTowerType = type;
        mImageComponent->SetTexture(towerIconPath);
        mRectComponent->SetSize(GetButtonSize());
    }

    void BuildingUISelectButton::OnMouseDownOnButton(const struct MouseButtonEventData &eventData)
    {
        // TODO: Implementation
    }

    void BuildingUISelectButton::OnMouseUpOnButton(const struct MouseButtonEventData &eventData, bool clickedSuccessfully)
    {
        if(clickedSuccessfully)
        {
            Tower* tower = Tower::CreateTowerFromType(mGame, mTowerType);
            if(tower != nullptr)
            {
                Transform& transform = (Transform&)tower->GetTransform();
                transform.SetPosition(eventData.mouseWorldPosition);
                mPlayer->SetPlacedTower(tower);
            }
        }
    }

    void BuildingUISelectButton::OnMouseEnterButton(const struct MouseMoveEventData &eventData)
    {
        // TODO: Implementation
    }

    void BuildingUISelectButton::OnMouseExitButton(const struct MouseMoveEventData &eventData)
    {
        // TODO: Implementation
    }
}