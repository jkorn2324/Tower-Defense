#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "Transform.h"
#include "EventListener.h"

namespace TowerDefense
{

	class Actor
	{
	public:
		explicit Actor(class Game* game);
		~Actor();

	public:
		void OnActorSpawn();

	public:
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

	public:
		Actor* GetParent() const;
		bool HasParent() const;
		void SetParent(Actor* actor, bool useScale = false);
        void RemoveParent();
		bool IsChild(Actor* actor) const;
		const std::vector<Actor*>& GetChildren() const;

	public:
		const GenericEventListener<Actor*>& GetDespawnListener() const;

	private:
	    void SetParentActive(bool active);
	    void UpdateChildrenParentActive(bool active);

	private:
		void AddChild(class Actor* actor);
		void RemoveChild(class Actor* actor);

	protected:
		Transform mTransform;

	private:
		bool mActive;
		bool mParentActive;

	protected:
		class ActorManager* mActorManager;
		class Game* mGame;

	private:
		std::vector<class Actor*> mChildren;
		std::vector<class Component*> mComponents;

	private:
		bool mQueuedForDespawn;
		float mDespawnTime, mMaxDespawnTime;
		GenericEventListener<class Actor*> mDespawnedListener;
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