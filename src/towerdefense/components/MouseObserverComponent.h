#pragma once

#include "Component.h"
#include "Mouse.h"
#include "EventCallback.h"

#include <functional>

namespace TowerDefense
{

    class MouseObserverComponent : public Component,
            public GenericEventObserver<MouseButtonEventData>,
            public GenericEventObserver<MouseMoveEventData>
    {
    public:
        explicit MouseObserverComponent(class Actor* owner);
        virtual ~MouseObserverComponent();

    public:
        void SetMouseDownCallback(std::function<void(const MouseButtonEventData&)> func);
        void SetMouseUpCallback(std::function<void(const MouseButtonEventData&)> func);
        void SetMouseMoveCallback(std::function<void(const MouseMoveEventData&)> func);

    protected:
        virtual void OnEventTriggered(const MouseButtonEventData& data) override;
        virtual void OnEventTriggered(const MouseMoveEventData& data) override;

    private:
        GenericEventCallback<const MouseButtonEventData&>* mMouseDownCallback;
        GenericEventCallback<const MouseButtonEventData&>* mMouseUpCallback;
        GenericEventCallback<const MouseMoveEventData&>* mMouseMoveCallback;
    };
}