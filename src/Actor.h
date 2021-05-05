#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "Transform.h"

namespace TowerDefense
{

	class Actor
	{

	public:
		Actor(class Game* game);
		~Actor();

	public:
		void OnActorSpawn();

	public:
		void UpdateTransform();
		void ProcessInput(const Uint8* keyState);
		void Update(float deltaTime);
		void Despawn();
		void Despawn(float despawnTime);

	protected:
		virtual void OnProcessInput(const Uint8* keyState);
		virtual void OnSpawn();
		virtual void OnUpdate(float deltaTime);
		virtual void OnDespawn();

	private:
		void UpdateDespawn(float deltaTime);

	public:
		void SetActive(bool active);
		bool IsActive() const;

	public:
		void AddComponent(class Component* component);

	public:
		template <typename T>
		T* GetComponent() const;
		const Transform& GetTransform() const;
		class Game* GetGame() const;
		class ActorManager* GetActorManager() const;

	protected:
		Transform mTransform;

	private:
		bool mActive;

	private:
		class ActorManager* mActorManager;
		class Game* mGame;

	private:
		std::vector<class Component*> mComponents;

	private:
		bool mQueuedForDespawn;
		float mDespawnTime, mMaxDespawnTime;
	};

	template<typename T>
	T* Actor::GetComponent() const
	{
		for (const auto& component : mComponents)
		{
			T* casted = dynamic_cast<T*>(component);
			if (casted != nullptr)
			{
				return casted;
			}
		}
		return nullptr;
	}
}