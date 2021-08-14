#include "MouseObserverComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mouse.h"
#include "EventCallback.h"

namespace TowerDefense
{

    MouseObserverComponent::MouseObserverComponent(Actor *owner)
            : Component(owner),
            GenericEventObserver<MouseButtonEventData>(
                    owner->GetGame()->GetMouse()->GetClickListener()),
                    GenericEventObserver<MouseMoveEventData>(
                      owner->GetGame()->GetMouse()->GetMoveListener())
    {
        mMouseDownCallback = new GenericEventCallback<const MouseButtonEventData&>();
        mMouseUpCallback = new GenericEventCallback<const MouseButtonEventData&>();
        mMouseMoveCallback = new GenericEventCallback<const MouseMoveEventData&>();
    }

    MouseObserverComponent::~MouseObserverComponent()
    {
        delete mMouseDownCallback;
        delete mMouseUpCallback;
        delete mMouseMoveCallback;
    }

    void MouseObserverComponent::SetMouseDownCallback(std::function<void(const MouseButtonEventData &)> func)
    {
        mMouseDownCallback->SetCallback(func);
    }

    void MouseObserverComponent::SetMouseUpCallback(std::function<void(const MouseButtonEventData&)> func)
    {
        mMouseUpCallback->SetCallback(func);
    }

    void MouseObserverComponent::SetMouseMoveCallback(std::function<void(const MouseMoveEventData &)> func)
    {
        mMouseMoveCallback->SetCallback(func);
    }

    void MouseObserverComponent::OnEventTriggered(const MouseButtonEventData &data)
    {
        switch(data.clickType)
        {
            case MouseEventType::BUTTON_UP:
                mMouseUpCallback->Invoke(data);
                break;
            case MouseEventType::BUTTON_DOWN:
                mMouseDownCallback->Invoke(data);
                break;
        }
    }

    void MouseObserverComponent::OnEventTriggered(const MouseMoveEventData &data)
    {
        mMouseMoveCallback->Invoke(data);
    }
}