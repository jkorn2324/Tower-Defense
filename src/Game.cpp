#include "Game.h"
#include "GameRenderer.h"
#include "ActorManager.h"
#include "TexturesManager.h"
#include "GameParameters.h"

namespace TowerDefense
{

	Game::Game()
	{
		mRenderer = new GameRenderer(this);
		mActorManager = new ActorManager(this);
		mTextureManager = new TexturesManager(this);
		mRunning = false;
		mPrevGameTick = SDL_GetTicks();
	}

	Game::~Game() { }

	GameRenderer* Game::GetRenderer() const { return mRenderer; }

	ActorManager* Game::GetActorManager() const { return mActorManager; }

	TexturesManager* Game::GetTexturesManager() const { return mTextureManager; }

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
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				mRunning = false;
				return;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			mRunning = false;
			return;
		}
		// TODO: Process input for actors
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
		delete mRenderer, mActorManager, mTextureManager;
	}
}