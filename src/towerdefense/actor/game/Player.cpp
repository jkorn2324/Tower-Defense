#include "Player.h"

#include "MouseObserverComponent.h"
#include "Mouse.h"
#include "Game.h"
#include "GameRenderer.h"
#include "LevelManager.h"
#include "Level.h"
#include "Tower.h"
#include "TowerManager.h"
#include "ActorManager.h"
#include "BuildingUI.h"
#include "GameUIActor.h"

#include "GreenCannonTower.h"

namespace TowerDefense
{

    Player::Player(Game* game)
        : Actor(game)
    {
        mPlacedTower = nullptr;
        mSelectedTower = nullptr;
        mMouseObserverComponent = new MouseObserverComponent(this);
        mMouseObserverComponent->SetMouseUpCallback(
                std::bind(&Player::OnMouseUp, this, std::placeholders::_1));
        mMouseObserverComponent->SetMouseDownCallback(
                std::bind(&Player::OnMouseDown, this, std::placeholders::_1));
    }

    void Player::OnProcessInput(const Uint8 *key)
    {
        if(key[SDL_SCANCODE_ESCAPE]
            && HasPlacedTower())
        {
            SetPlacedTower(nullptr);
        }
    }

    void Player::OnUpdate(float deltaTime)
    {
        UpdatePlacedTower(deltaTime);
    }

    bool Player::HasPlacedTower() const
    {
        return mPlacedTower != nullptr;
    }

    void Player::SetPlacedTower(Tower *tower)
    {
        if(HasPlacedTower() && !mPlacedTower->IsPlaced())
        {
            mPlacedTower->Despawn();
        }
        mPlacedTower = tower;
        SetTowerSelected(mPlacedTower);
    }

    void Player::SetTowerSelected(Tower *tower)
    {
        if(mSelectedTower != nullptr)
        {
            mSelectedTower->HighlightTowerRange(false);
        }

        mSelectedTower = tower;

        if(mSelectedTower != nullptr)
        {
            mSelectedTower->OnSelected();
            mSelectedTower->HighlightTowerRange(true);
        }
    }

    void Player::UpdatePlacedTower(float deltaTime)
    {
        if(HasPlacedTower()
            && !mPlacedTower->IsPlaced())
        {
            Vector2 screenPosition = mGame->GetMouse()->GetMousePosition();
            Vector2 worldPosition = mGame->GetRenderer()->ScreenToWorldPoint(
                    screenPosition);
            Transform& transform = (Transform&)mPlacedTower->GetTransform();
            transform.SetPosition(worldPosition);
        }
    }

    void Player::OnMouseDown(const MouseButtonEventData &eventData)
    {
        if(HasPlacedTower())
        {
            return;
        }

        Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
        Tower* selectedTower = activeLevel->GetTowerManager()
                ->GetTowerAtPosition(eventData.mouseWorldPosition);
        SetTowerSelected(selectedTower);
    }

    void Player::OnMouseUp(const MouseButtonEventData &eventData)
    {
        if(HasPlacedTower())
        {
            BuildingUI* buildingUI = mGame->GetActorManager()->GetBuildingUI();
            Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
            if(!mPlacedTower->IsPlaced()
                && activeLevel != nullptr
                && activeLevel->CanPlaceTower(eventData.mouseWorldPosition))
            {
                GameUIActor* actor = buildingUI
                        ->GetActorFromPosition(eventData.mouseWorldPosition);
                if(actor == nullptr)
                {
                    mPlacedTower->PlaceTower();
                    mPlacedTower = nullptr;
                }
            }
        }
    }
}