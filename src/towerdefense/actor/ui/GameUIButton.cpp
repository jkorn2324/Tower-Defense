//
// Created by jkorn on 8/8/2021.
//

#include "GameUIButton.h"

namespace TowerDefense
{

    GameUIButton::GameUIButton(class GameUI *gameUI)
            : GameUIActor(gameUI)
    {
    }

    void GameUIButton::OnMouseDown(const MouseButtonEventData &eventData)
    {
        SDL_Log("Mouse Down on Button");
    }

    void GameUIButton::OnMouseUp(const MouseButtonEventData& eventData)
    {
        SDL_Log("Mouse Up on Button");
    }

    void GameUIButton::OnMouseMove(const MouseMoveEventData &eventData)
    {
        SDL_Log("Mouse Move on Button");
    }
}
