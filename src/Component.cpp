#include "Component.h"
#include "Actor.h"

namespace TowerDefense
{

	Component::Component(Actor* actor)
	{
		mOwner = actor;
		mEnabled = true;
		mOwner->AddComponent(this);
	}

	Component::~Component() { }

	Actor* Component::GetOwner() const { return mOwner; }

	void Component::SetEnabled(bool enabled) { mEnabled = enabled; }

	bool Component::IsEnabled() const { return mEnabled; }

	void Component::OnSpawn() { }

	void Component::OnDespawn() { }

	void Component::ProcessInput(const Uint8* keyState) { }

	void Component::Update(float deltaTime) { }
}