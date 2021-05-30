#include "Actor.h"
#include "Game.h"
#include "ActorManager.h"
#include "Component.h"

namespace TowerDefense
{

	Actor::Actor(Game* game)
	{
		mComponents = std::vector<Component*>();
		mActive = true;
		mDespawnTime = mMaxDespawnTime = 0.0f;
		mQueuedForDespawn = false;
		mGame = game;
		mActorManager = game->GetActorManager();
		mTransform = Transform();
		mActorManager->AddActor(this);
	}

	Actor::~Actor()
	{
		for(Component* component : mComponents)
		{
			if (component != nullptr)
			{
				delete component;
			}
		}
		mComponents.clear();
	}

	void Actor::AddComponent(Component* component)
	{
		const auto& output = std::find(mComponents.begin(), mComponents.end(), component);
		if (output != mComponents.end())
		{
			return;
		}
		mComponents.push_back(component);
	}

	bool Actor::IsActive() const { return mActive; }

	void Actor::SetActive(bool active) { mActive = active; }

	Game* Actor::GetGame() const
	{
		return mGame;
	}

	ActorManager* Actor::GetActorManager() const
	{
		return mActorManager;
	}

	const Transform& Actor::GetTransform() const { return mTransform;  }

	void Actor::OnActorSpawn()
	{
		for (Component* component : mComponents)
		{
			component->OnSpawn();
		}
		OnSpawn();
	}

	void Actor::OnSpawn() { }

	void Actor::Despawn()
	{
		if (mQueuedForDespawn)
		{
			mQueuedForDespawn = false;
		}

		for (Component* component : mComponents)
		{
			component->OnDespawn();
		}
		OnDespawn();
		mActorManager->RemoveActor(this);
	}

	void Actor::Despawn(float maxDespawnTime)
	{
		if (maxDespawnTime <= 0.0f)
		{
			Despawn();
			return;
		}
		mDespawnTime = 0.0f;
		mMaxDespawnTime = maxDespawnTime;
		mQueuedForDespawn = true;
	}

	void Actor::OnDespawn() { }

	void Actor::Update(float deltaTime)
	{
		for (Component* component : mComponents)
		{
			component->Update(deltaTime);
		}
		OnUpdate(deltaTime);
		UpdateDespawn(deltaTime);
	}

	void Actor::UpdateTransform()
	{
		mTransform.CalculateTransformMatrix();
	}

	void Actor::ProcessInput(const Uint8* keyState)
	{
		for (Component* component : mComponents)
		{
			component->ProcessInput(keyState);
		}
		OnProcessInput(keyState);
	}

	void Actor::OnProcessInput(const Uint8* keyState) { }

	void Actor::OnUpdate(float deltaTime) { }

	void Actor::UpdateDespawn(float deltaTime)
	{
		if (mQueuedForDespawn)
		{
			mDespawnTime += deltaTime;

			if (mDespawnTime >= mMaxDespawnTime)
			{
				Despawn();
			}
		}
	}
}