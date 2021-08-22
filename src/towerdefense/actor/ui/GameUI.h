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
        GameUI(class Game* game, const Vector2& uiSize);
        virtual ~GameUI();

    public:
        const Vector2& GetSize() const;
        /**
         * Gets the scaled vector2 from an x & y that is each between 0 & 1.
         * @param x - The x position.
         * @param y - The y position.
         * @return Vector2
         */
        Vector2 GetScaledVector2(float x, float y) const;

    public:
        class GameUIActor* GetActorFromPosition(const Vector2& position) const;

    private:
        void AddUIActor(class GameUIActor* uiActor);
        void RemoveUIActor(class GameUIActor* uiActor);

    private:
        Vector2 mUISize;
        std::vector<class GameUIActor*> mUIActors;

    public:
        friend class GameUIActor;
    };
}