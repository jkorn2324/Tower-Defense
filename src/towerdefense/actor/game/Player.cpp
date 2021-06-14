#include "Player.h"

#include "MouseObserverComponent.h"
#include "Mouse.h"
#include "Game.h"
#include "GameRenderer.h"
#include "LevelManager.h"
#include "Level.h"
#include "Tower.h"

#include "GreenCannonTower.h"

namespace TowerDefense
{

    Player::Player(Game* game)
        : Actor(game)
    {
        mTowerSelected = nullptr;
        mMouseObserverComponent = new MouseObserverComponent(this);
        mMouseObserverComponent->SetMouseUpCallback(
                std::bind(&Player::OnMouseUp, this, std::placeholders::_1));
        SetTowerSelected(new GreenCannonTower(game));
    }

    void Player::OnUpdate(float deltaTime)
    {
        UpdateTower(deltaTime);
    }

    void Player::SetTowerSelected(Tower *tower)
    {
        if(mTowerSelected != nullptr && !mTowerSelected->IsPlaced())
        {
            mTowerSelected->Despawn();
        }
        mTowerSelected = tower;
    }

    void Player::UpdateTower(float deltaTime)
    {
        if(mTowerSelected != nullptr
            && !mTowerSelected->IsPlaced())
        {
            Vector2 screenPosition = mGame->GetMouse()->GetMousePosition();
            Vector2 worldPosition = mGame->GetRenderer()->ScreenToWorldPoint(
                    screenPosition);
            Transform& transform = (Transform&)mTowerSelected->GetTransform();
            transform.SetPosition(worldPosition);
        }
    }

    void Player::OnMouseUp(const MouseButtonEventData &eventData)
    {
        if(mTowerSelected != nullptr)
        {
            Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
            if(activeLevel != nullptr
               && activeLevel->CanPlaceTower(eventData.mouseWorldPosition)
               && !mTowerSelected->IsPlaced())
            {
                mTowerSelected->PlaceTower();
                mTowerSelected = nullptr;
            }
        }
    }
}