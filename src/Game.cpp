#include "Game.h"
#include "GameRenderer.h"
#include "ActorManager.h"
#include "GameParameters.h"

namespace TowerDefense
{

	Game::Game()
	{
		mRenderer = new GameRenderer(this);
		mActorManager = new ActorManager(this);
		mRunning = false;
		mPrevGameTick = SDL_GetTicks();
	}

	Game::~Game() { }

	GameRenderer* Game::GetRenderer() const { return mRenderer; }

	ActorManager* Game::GetActorManager() const
	{
		return mActorManager;
	}

	bool Game::InitializeGame()
	{
		if (!mRenderer->Initialize())
		{
			return false;
		}

		LoadGame();
		mRunning = true;
		return true;
	}

	void Game::LoadGame()
	{
		mPrevGameTick = SDL_GetTicks();
		// TODO: Implementation
	}

	void Game::RunGame()
	{
		while (mRunning)
		{
			ProcessInput();
			UpdateGame();
			GenerateOutput();
		}
	}

	void Game::ProcessInput()
	{
	}

	void Game::UpdateGame()
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mPrevGameTick + WAIT_TIME_TICKS));
		Uint32 currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - mPrevGameTick) / 1000.0f;
		mActorManager->Update(deltaTime);
		mPrevGameTick = currentTicks;
	}

	void Game::GenerateOutput()
	{
		mRenderer->Render();
	}

	void Game::ShutdownGame()
	{
		if (mRunning)
		{
			mRunning = false;
		}
		mRenderer->Uninitialize();
		delete mRenderer, mActorManager;
	}
}