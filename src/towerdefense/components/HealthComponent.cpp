#include "HealthComponent.h"

#include "Actor.h"
#include "GameMath.h"

namespace TowerDefense
{

    HealthComponent::HealthComponent(Actor *owner)
            : Component(owner)
    {
        mHealthChanged = GenericEventCallback<const HealthChangedEventData&>();
        mHealth = mMaxHealth = MAX_DEFAULT_HEALTH;
    }

    HealthComponent::HealthComponent(float maxHealth, Actor *owner)
        : Component(owner)
    {
        mHealthChanged = GenericEventCallback<const HealthChangedEventData&>();
        mHealth = mMaxHealth = maxHealth;
    }

    void HealthComponent::SetHealthChangedCallback(std::function<void(const HealthChangedEventData &)> func)
    {
        mHealthChanged.SetCallback(func);
    }

    void HealthComponent::SetHealth(float newHealth)
    {
        newHealth = Clamp(newHealth, 0.0f, mMaxHealth);
        if(newHealth != mHealth)
        {
            HealthChangedEventData eventData;
            eventData.oldHealth = mHealth;
            eventData.newHealth = newHealth;
            mHealthChanged.Invoke(eventData);
        }
        mHealth = newHealth;
    }

    float HealthComponent::GetHealth() const { return mHealth; }

    void HealthComponent::SetMaxHealth(float maxHealth, bool setHealth)
    {
        mMaxHealth = maxHealth;

        if(setHealth)
        {
            SetHealth(mMaxHealth);
        }
    }

    float HealthComponent::GetMaxHealth() const { return mMaxHealth; }
}
