#pragma once

#include <functional>
#include <vector>
#include <algorithm>

namespace TowerDefense
{

    class EventListener;
    template<typename T>
    class GenericEventListener;

    /**
     * The Event Observer class.
     */
    class EventObserver
    {
    public:
        explicit EventObserver(EventListener* listener);
        virtual ~EventObserver();

    public:
        virtual void OnEventTriggered()=0;

    private:
        EventListener* mListener;
    };

    /**
     * The Event Observer as a generic.
     * @tparam T - The Generic parameter.
     */
    template<typename T>
    class GenericEventObserver
    {
    public:
        explicit GenericEventObserver(GenericEventListener<T>* listener);
        virtual ~GenericEventObserver();

    protected:
        virtual void OnEventTriggered(const T& args)=0;

    private:
        GenericEventListener<T>* mListener;

    public:
        friend class GenericEventListener<T>;
    };

    template<typename T>
    GenericEventObserver<T>::GenericEventObserver(GenericEventListener<T> *listener)
    {
        mListener = listener;
        mListener->AddObserver(*this);
    }

    template<typename T>
    GenericEventObserver<T>::~GenericEventObserver()
    {
        mListener->RemoveObserver(*this);
    }

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

    /**
     * A Generic event listener, used for events with more than 1 parameter.
     * @tparam T - The type for the parameter.
     */
    template<typename T>
    class GenericEventListener
    {
    public:
        GenericEventListener();
        ~GenericEventListener();

    public:
        void Invoke(const T& args);
        void AddObserver(GenericEventObserver<T>& observer);
        void RemoveObserver(GenericEventObserver<T>& observer);

    public:
        GenericEventObserver<T>& operator+=(GenericEventObserver<T>& observer);
        GenericEventObserver<T>& operator-=(GenericEventObserver<T>& observer);

    private:
        std::vector<GenericEventObserver<T>*> mObservers;
    };


    template<typename T>
    GenericEventListener<T>::GenericEventListener()
    {
        mObservers = std::vector<GenericEventObserver<T>*>();
    }

    template<typename T>
    GenericEventListener<T>::~GenericEventListener()
    {
        mObservers.clear();
    }

    template<typename T>
    void GenericEventListener<T>::Invoke(const T &args)
    {
        int size = static_cast<int>(mObservers.size());
        for(int i = size - 1; i >= 0; i--)
        {
            mObservers[i]->OnEventTriggered(args);
        }
    }

    template<typename T>
    GenericEventObserver<T>& GenericEventListener<T>::operator+=(GenericEventObserver<T> &observer)
    {
        AddObserver(observer);
        return *this;
    }

    template<typename T>
    GenericEventObserver<T>& GenericEventListener<T>::operator-=(GenericEventObserver<T> &observer)
    {
        RemoveObserver(observer);
        return *this;
    }

    template<typename T>
    void GenericEventListener<T>::AddObserver(GenericEventObserver<T> &observer)
    {
        const auto& observerFound = std::find(mObservers.begin(), mObservers.end(), &observer);
        if(observerFound != mObservers.end())
        {
            return;
        }
        mObservers.push_back(&observer);
    }

    template<typename T>
    void GenericEventListener<T>::RemoveObserver(GenericEventObserver<T> &observer)
    {
        const auto& observerFound = std::find(mObservers.begin(), mObservers.end(), &observer);
        mObservers.erase(observerFound);
    }
}
