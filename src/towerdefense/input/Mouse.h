#pragma once

#include "Vector2.h"
#include "EventListener.h"

#include <SDL2/SDL.h>

namespace TowerDefense
{

    enum MouseButtonType
    {
        RIGHT_CLICK,
        LEFT_CLICK
    };

    enum MouseButtonClickType
    {
        BUTTON_UP,
        BUTTON_DOWN
    };

    struct MouseButtonEventData
    {
        MouseButtonType buttonType;
        MouseButtonClickType clickType;
        Vector2 mouseScreenPosition;
        Vector2 mouseWorldPosition;
    };

    class Mouse
    {
    public:
        explicit Mouse(class Game* game);
        ~Mouse();

    public:
        bool Initialize();
        void Update();

    public:
        const Vector2& GetMousePosition() const;
        const Vector2& GetDeltaPosition() const;

    public:
        GenericEventListener<MouseButtonEventData>* GetListener() const;
        bool IsHidden() const;
        void SetHidden(bool hidden);

    private:
        void OnMouseDown(SDL_MouseButtonEvent& button);
        void OnMouseUp(SDL_MouseButtonEvent& button);

    private:
        bool mHidden;
        Vector2 mDeltaPosition;
        Vector2 mPosition;
        GenericEventListener<MouseButtonEventData>* mListener;
        class Game* mGame;

    public:
        friend class Game;
    };
}