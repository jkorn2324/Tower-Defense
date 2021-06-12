#include "MouseObserverComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mouse.h"
#include "EventCallback.h"

namespace TowerDefense
{

    MouseObserverComponent::MouseObserverComponent(Actor *owner)
            : Component(owner), GenericEventObserver<MouseButtonEventData>(
                    owner->GetGame()->GetMouse()->GetListener())
    {
        mMouseDownCallback = new EventCallback<const MouseButtonEventData&>();
        mMouseUpCallback = new EventCallback<const MouseButtonEventData&>();
    }

    MouseObserverComponent::~MouseObserverComponent()
    {
        Component::~Component();
        GenericEventObserver<MouseButtonEventData>::~GenericEventObserver();

        delete mMouseDownCallback;
        delete mMouseUpCallback;
    }

    void MouseObserverComponent::SetMouseDownCallback(std::function<void(const MouseButtonEventData &)> func)
    {
        mMouseDownCallback->SetCallback(func);
    }

    void MouseObserverComponent::SetMouseUpCallback(std::function<void(const MouseButtonEventData&)> func)
    {
        mMouseUpCallback->SetCallback(func);
    }

    void MouseObserverComponent::OnEventTriggered(const MouseButtonEventData &data)
    {
        switch(data.clickType)
        {
            case MouseButtonClickType::BUTTON_UP:
                mMouseUpCallback->Invoke(data);
                break;
            case MouseButtonClickType::BUTTON_DOWN:
                mMouseDownCallback->Invoke(data);
                break;
        }
    }
}