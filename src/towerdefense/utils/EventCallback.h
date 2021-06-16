#pragma once

#include <functional>

namespace TowerDefense
{

    /**
     * The Event Callback.
     */
     template <typename T>
    class EventCallback
    {
    public:
        EventCallback() { mFunc = nullptr; }
        EventCallback(std::function<void(T)> func) { mFunc = func; }
        ~EventCallback() = default;

    public:
        void SetCallback(std::function<void(T)> func) { mFunc = func; }
        void Invoke(T param)
        {
            if(mFunc != nullptr) { mFunc(param); }
        }

    private:
        std::function<void(T)> mFunc;
    };
}
