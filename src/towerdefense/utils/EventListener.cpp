#include "EventListener.h"

namespace TowerDefense
{

    // ------------------------ The Event Observer Class -----------------------

    EventObserver::EventObserver(EventListener* listener)
    {
        mListener = listener;
        listener->AddObserver(*this);
    }

    EventObserver::~EventObserver()
    {
        mListener->RemoveObserver(*this);
    }

    // ------------------------- The Event Listener Class ------------------------

    EventListener::EventListener()
    {
        mObservers = std::vector<EventObserver*>();
    }

    EventListener::~EventListener()
    {
        mObservers.clear();
    }

    void EventListener::Invoke()
    {
        int size = static_cast<int>(mObservers.size());
        for(int i = size - 1; i >= 0; i--)
        {
            mObservers[i]->OnEventTriggered();
        }
    }

    void EventListener::AddObserver(EventObserver &observer)
    {
        const auto& observerFound = std::find(mObservers.begin(), mObservers.end(), &observer);
        if(observerFound != mObservers.end())
        {
            return;
        }
        mObservers.push_back(&observer);
    }

    void EventListener::RemoveObserver(EventObserver &observer)
    {
        const auto& observerFound = std::find(mObservers.begin(), mObservers.end(), &observer);
        mObservers.erase(observerFound);
    }

    EventListener& EventListener::operator+=(EventObserver& observer)
    {
        AddObserver(observer);
        return *this;
    }

    EventListener& EventListener::operator-=(EventObserver& observer)
    {
        RemoveObserver(observer);
        return *this;
    }
}
