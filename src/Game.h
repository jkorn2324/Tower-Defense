#pragma once

#include <SDL2/SDL.h>

namespace TowerDefense
{


	class Game
	{
	public:
		Game();
		~Game();

	public:
		bool InitializeGame();
		void RunGame();
		void ShutdownGame();

	private:
		void LoadGame();
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();

	public:
		class GameRenderer* GetRenderer() const;
		class ActorManager* GetActorManager() const;

	private:
		bool mRunning;
		Uint32 mPrevGameTick;

	private:
		class GameRenderer* mRenderer;
		class ActorManager* mActorManager;
	};
}