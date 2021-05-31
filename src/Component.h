#pragma once

#include <SDL2/SDL.h>

namespace TowerDefense
{

	class Component
	{

	public:
		Component(class Actor* owner);
		virtual ~Component();

	public:
		void SetEnabled(bool enabled);
		bool IsEnabled() const;
		class Actor* GetOwner() const;

	public:
		virtual void OnSpawn();
		virtual void OnDespawn();
		virtual void ProcessInput(const Uint8* keyState);
		virtual void Update(float deltaTime);

	protected:
		class Actor* mOwner;
		class Transform* mTransform;

	private:
		bool mEnabled;
	};
}