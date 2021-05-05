#pragma once

#include <vector>
#include <SDL2/SDL.h>

namespace TowerDefense
{


	class ActorManager
	{

	public:
		ActorManager(class Game* game);
		~ActorManager();

	public:
		void ProcessInput(const Uint8* keyboardState);
		void Update(float deltaTime);
		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* actor);

	public:
		class Game* GetGame() const;

	private:
		void HandleSpawn(class Actor* actor);
		void HandleDespawn(class Actor* actor);

	private:
		std::vector<class Actor*> mSpawnActors;
		std::vector<class Actor*> mDespawnActors;
		std::vector<class Actor*> mActors;

	private:
		class Game* mGame;
	};
}