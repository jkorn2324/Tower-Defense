#include "Player.h"

#include "MouseObserverComponent.h"
#include "Mouse.h"
#include "Game.h"
#include "GameRenderer.h"
#include "LevelManager.h"
#include "Level.h"
#include "Tower.h"
#include "TowerManager.h"

#include "GreenCannonTower.h"

namespace TowerDefense
{

    Player::Player(Game* game)
        : Actor(game)
    {
        mPlacedTower = nullptr;
        mHighlightedTower = nullptr;
        mMouseObserverComponent = new MouseObserverComponent(this);
        mMouseObserverComponent->SetMouseUpCallback(
                std::bind(&Player::OnMouseUp, this, std::placeholders::_1));
        mMouseObserverComponent->SetMouseDownCallback(
                std::bind(&Player::OnMouseDown, this, std::placeholders::_1));
        SetTowerSelected(new GreenCannonTower(game));
    }

    void Player::OnUpdate(float deltaTime)
    {
        UpdatePlacedTower(deltaTime);
    }

    void Player::SetTowerSelected(Tower *tower)
    {
        if(mPlacedTower != nullptr && !mPlacedTower->IsPlaced())
        {
            mPlacedTower->Despawn();
        }
        mPlacedTower = tower;
        SetTowerHighlighted(mPlacedTower);
    }

    void Player::SetTowerHighlighted(Tower *tower)
    {
        if(mHighlightedTower != nullptr)
        {
            mHighlightedTower->HighlightTowerRange(false);
        }

        mHighlightedTower = tower;
        if(mHighlightedTower != nullptr)
        {
            mHighlightedTower->HighlightTowerRange(true);
        }
    }

    void Player::UpdatePlacedTower(float deltaTime)
    {
        if(mPlacedTower != nullptr
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
        if(mPlacedTower != nullptr)
        {
            return;
        }

        Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
        Tower* selectedTower = activeLevel->GetTowerManager()
                ->GetTowerAtPosition(eventData.mouseWorldPosition);
        SetTowerHighlighted(selectedTower);
    }

    void Player::OnMouseUp(const MouseButtonEventData &eventData)
    {
        if(mPlacedTower != nullptr)
        {
            Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
            if(activeLevel != nullptr
               && activeLevel->CanPlaceTower(eventData.mouseWorldPosition)
               && !mPlacedTower->IsPlaced())
            {
                mPlacedTower->PlaceTower();
                mPlacedTower = nullptr;
            }
        }
    }
}