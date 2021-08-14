//
// Created by jkorn on 8/8/2021.
//

#include "GameUIActor.h"

#include "GameUI.h"
#include "Game.h"
#include "MouseObserverComponent.h"

#include <functional>

namespace TowerDefense
{

    GameUIActor::GameUIActor(GameUI *ui)
            : Actor(ui->GetGame())
    {
        mGameUI = ui;
        mMouseObserverComponent = new MouseObserverComponent(this);
        mMouseObserverComponent->SetMouseDownCallback(
                std::bind(&GameUIActor::OnMouseDown, this, std::placeholders::_1));
        mMouseObserverComponent->SetMouseUpCallback(
                std::bind(&GameUIActor::OnMouseUp, this, std::placeholders::_1));
        mMouseObserverComponent->SetMouseMoveCallback(
                std::bind(&GameUIActor::OnMouseMove, this, std::placeholders::_1));
        mGameUI->AddUIActor(this);
    }

    GameUIActor::~GameUIActor()
    {
        mGameUI->RemoveUIActor(this);
    }
}