//
// Created by jkorn on 8/8/2021.
//

#include "GameUI.h"

#include <vector>

#include "GameUIActor.h"

namespace TowerDefense
{

    GameUI::GameUI(class Game *game)
            : Actor(game)
    {
        mUIActors = std::vector<GameUIActor*>();
    }

    GameUI::~GameUI()
    {
        for(const auto& actor : mUIActors)
        {
            actor->Despawn();
        }
        mUIActors.clear();
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