#pragma once

#include "Component.h"
#include "EventCallback.h"

namespace TowerDefense
{

    const float MAX_DEFAULT_HEALTH = 10.0f;

    /**
     * The health changed event data.
     */
    struct HealthChangedEventData
    {
        float oldHealth;
        float newHealth;
    };

    /**
     * The health component.
     */
    class HealthComponent : public Component
    {
    public:
        HealthComponent(class Actor* owner);
        HealthComponent(float maxHealth, class Actor* owner);

    public:
        void SetHealthChangedCallback(std::function<void(const HealthChangedEventData&)> func);
        void SetMaxHealth(float maxHealth, bool setHealth = false);
        float GetMaxHealth() const;
        void SetHealth(float newHealth);
        float GetHealth() const;
        float GetHealthPercentage() const;

    private:
        float mHealth;
        float mMaxHealth;
        EventCallback<const HealthChangedEventData&> mHealthChanged;
    };
}