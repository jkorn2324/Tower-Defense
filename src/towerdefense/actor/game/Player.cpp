#include "Player.h"

#include "MouseObserverComponent.h"
#include "Mouse.h"
#include "Game.h"
#include "GameRenderer.h"
#include "LevelManager.h"
#include "Level.h"

namespace TowerDefense
{

    Player::Player(Game* game)
        : Actor(game)
    {
        mMouseObserverComponent = new MouseObserverComponent(this);
        mMouseObserverComponent->SetMouseUpCallback(
                std::bind(&Player::OnMouseUp, this, std::placeholders::_1));
    }

    void Player::OnMouseUp(const MouseButtonEventData &eventData)
    {
        Level* activeLevel = mGame->GetLevelManager()->GetActiveLevel();
        if(activeLevel != nullptr
            && activeLevel->CanPlaceTower(eventData.mouseWorldPosition))
        {
            SDL_Log("Place tower!");
        }
    }
}