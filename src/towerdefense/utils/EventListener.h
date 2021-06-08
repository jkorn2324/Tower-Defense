#pragma once

#include <functional>
#include <vector>

namespace TowerDefense
{

    class EventListener;

    /**
     * The Event Observer class.
     */
    class EventObserver
    {
    public:
        EventObserver(EventListener* listener);
        virtual ~EventObserver();

    public:
        virtual void Invoke()=0;

    private:
        EventListener* mListener;
    };

    /**
     * The Event Listener class with no parameters.
     */
    class EventListener
    {
    public:
        EventListener();
        ~EventListener();

    public:
        void Invoke();
        void AddObserver(EventObserver& observer);
        void RemoveObserver(EventObserver& observer);

    public:
        EventListener& operator+=(EventObserver& observer);
        EventListener& operator-=(EventObserver& observer);

    private:
        std::vector<EventObserver*> mObservers;
    };
}
