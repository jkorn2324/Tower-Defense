//
// Created by jkorn on 8/8/2021.
//

#include "GameUI.h"

#include <vector>

#include "GameUIActor.h"
#include "Game.h"
#include "GameRenderer.h"

namespace TowerDefense
{

    GameUI::GameUI(Game *game)
            : Actor(game)
    {
        mUIActors = std::vector<GameUIActor*>();
        mUISize = game->GetRenderer()->GetWindowSize();
    }

    GameUI::GameUI(class Game *game, const Vector2 &uiSize)
            : Actor(game)
    {
        mUIActors = std::vector<GameUIActor*>();
        mUISize = uiSize;
    }

    GameUI::~GameUI()
    {
        for(const auto& actor : mUIActors)
        {
            actor->Despawn();
        }
        mUIActors.clear();
    }

    const Vector2 & GameUI::GetSize() const { return mUISize; }

    Vector2 GameUI::GetScaledVector2(float x, float y) const
    {
        return Vector2(
                mUISize.x * x, mUISize.y * y);
    }

    GameUIActor* GameUI::GetActorFromPosition(const Vector2 &position) const
    {
        if(!IsActive())
        {
            return nullptr;
        }
        for(const auto& actor : mUIActors)
        {
            if(actor->IsWithinActor(position))
            {
                return actor;
            }
        }
        return nullptr;
    }

    void GameUI::AddUIActor(class GameUIActor *uiActor)
    {
        const auto& searchedActor = std::find(mUIActors.begin(), mUIActors.end(), uiActor);
        if(searchedActor == mUIActors.end())
        {
            uiActor->SetParent(this);
            mUIActors.push_back(uiActor);
        }
    }

    void GameUI::RemoveUIActor(class GameUIActor *uiActor)
    {
        const auto& searchedActor = std::find(mUIActors.begin(), mUIActors.end(), uiActor);
        if(searchedActor != mUIActors.end())
        {
            uiActor->SetParent(nullptr);
            mUIActors.erase(searchedActor);
        }
    }
}