#pragma once

#include "Component.h"
#include "Mouse.h"
#include "EventCallback.h"

#include <functional>

namespace TowerDefense
{

    class MouseObserverComponent : public Component, public GenericEventObserver<MouseButtonEventData>
    {
    public:
        explicit MouseObserverComponent(class Actor* owner);
        virtual ~MouseObserverComponent();

    public:
        void SetMouseDownCallback(std::function<void(const MouseButtonEventData&)> func);
        void SetMouseUpCallback(std::function<void(const MouseButtonEventData&)> func);

    protected:
        virtual void OnEventTriggered(const MouseButtonEventData& data) override;

    private:
        GenericEventCallback<const MouseButtonEventData&>* mMouseDownCallback;
        GenericEventCallback<const MouseButtonEventData&>* mMouseUpCallback;
    };
}