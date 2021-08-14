#pragma once

#include "Vector2.h"
#include "EventListener.h"

#include <SDL2/SDL.h>

namespace TowerDefense
{

    enum MouseButtonType
    {
        RIGHT_CLICK,
        LEFT_CLICK,
    };

    enum MouseEventType
    {
        BUTTON_UP,
        BUTTON_DOWN
    };

    struct MouseButtonEventData
    {
        MouseButtonType buttonType;
        MouseEventType clickType;
        Vector2 mouseScreenPosition;
        Vector2 mouseWorldPosition;
    };

    struct MouseMoveEventData
    {
        Vector2 newMouseScreenPos;
        Vector2 newMouseWorldPos;
        Vector2 prevMouseScreenPos;
        Vector2 prevMouseWorldPos;
    };

    class Mouse
    {
    public:
        explicit Mouse(class Game* game);
        ~Mouse();

    public:
        bool Initialize();

    public:
        const Vector2& GetMousePosition() const;
        const Vector2& GetDeltaPosition() const;

    public:
        GenericEventListener<MouseButtonEventData>* GetClickListener() const;
        GenericEventListener<MouseMoveEventData>* GetMoveListener() const;
        bool IsHidden() const;
        void SetHidden(bool hidden);

    private:
        void OnMouseMove(SDL_MouseMotionEvent& event);
        void OnMouseDown(SDL_MouseButtonEvent& button);
        void OnMouseUp(SDL_MouseButtonEvent& button);

    private:
        bool mHidden;
        Vector2 mDeltaPosition;
        Vector2 mPosition;
        GenericEventListener<MouseButtonEventData>* mClickListener;
        GenericEventListener<MouseMoveEventData>* mMoveListener;
        class Game* mGame;

    public:
        friend class Game;
    };
}