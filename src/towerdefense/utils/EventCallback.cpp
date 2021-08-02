#include "EventCallback.h"

namespace TowerDefense
{

    EventObserverCallback::EventObserverCallback(class EventListener *listener)
            : EventObserver(listener)
    {
        mFunc = nullptr;
    }

    void EventObserverCallback::SetCallback(std::function<void()> func)
    {
        mFunc = func;
    }

    void EventObserverCallback::OnEventTriggered()
    {
        if(mFunc != nullptr)
        {
            mFunc();
        }
    }
}