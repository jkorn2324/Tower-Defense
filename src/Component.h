#pragma once

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
		virtual void Update(float deltaTime)=0;

	private:
		bool mEnabled;
		class Actor* mOwner;
	};
}