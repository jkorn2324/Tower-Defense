//
// Created by jkorn on 8/8/2021.
//

#pragma once

#include "Actor.h"

#include <vector>

namespace TowerDefense
{

    class GameUI : public Actor
    {
    public:
        explicit GameUI(class Game* game);
        virtual ~GameUI();

    private:
        void AddUIActor(class GameUIActor* uiActor);
        void RemoveUIActor(class GameUIActor* uiActor);

    private:
        std::vector<class GameUIActor*> mUIActors;

    public:
        friend class GameUIActor;
    };
}