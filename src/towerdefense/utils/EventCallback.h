#pragma once

#include <functional>

#include "EventListener.h"

namespace TowerDefense
{

    class EventCallback
    {
    public:
        EventCallback() { mFunc = nullptr; }
        EventCallback(std::function<void()> func) { mFunc = func; }
        ~EventCallback() = default;

    public:
        void SetCallback(std::function<void()> func) { mFunc = func; }
        void Invoke()
        {
            if(mFunc != nullptr) { mFunc(); }
        }

    private:
        std::function<void()> mFunc;
    };

#pragma region event_observer_callback

    class EventObserverCallback : public EventObserver
    {
    public:
        EventObserverCallback(class EventListener* listener);

    public:
        void SetCallback(std::function<void()> func);

    protected:
        void OnEventTriggered() override;

    private:
        std::function<void()> mFunc;
    };

#pragma endregion

#pragma region generic_event_callback

    /**
     * The Generic Event Callback.
     */
     template <typename T>
    class GenericEventCallback
    {
    public:
        GenericEventCallback() { mFunc = nullptr; }
        GenericEventCallback(std::function<void(T)> func) { mFunc = func; }
        ~GenericEventCallback() = default;

    public:
        void SetCallback(std::function<void(T)> func) { mFunc = func; }
        void Invoke(T param)
        {
            if(mFunc != nullptr) { mFunc(param); }
        }

    private:
        std::function<void(T)> mFunc;
    };

#pragma endregion

#pragma region generic_event_observer_callback

     template <typename T>
     class GenericEventObserverCallback : public GenericEventObserver<T>
     {
     public:
         GenericEventObserverCallback<T>(GenericEventListener<T>* listener)
                 : GenericEventObserver<T>(listener)
         {
             mFunc = nullptr;
         }

     public:
         void SetCallback(std::function<void(const T&)> func)
         {
             mFunc = func;
         }

     protected:
         void OnEventTriggered(const T& arg) override
         {
             if(mFunc != nullptr)
             {
                 mFunc(arg);
             }
         }

     private:
         std::function<void(const T&)> mFunc;
     };

#pragma endregion
}
