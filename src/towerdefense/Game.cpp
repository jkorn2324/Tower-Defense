#include "Game.h"
#include "GameRenderer.h"
#include "ActorManager.h"
#include "LevelManager.h"
#include "TexturesManager.h"
#include "GameParameters.h"
#include "JSONHelper.h"

namespace TowerDefense
{

	Game::Game()
	{
		mRenderer = new GameRenderer(this);
		mActorManager = new ActorManager(this);
		mTextureManager = new TexturesManager(this);
		mLevelManager = new LevelManager(this);
		mRunning = false;
		mPrevGameTick = SDL_GetTicks();
	}

	LevelManager* Game::GetLevelManager() const
	{
		return mLevelManager;
	}

	GameRenderer* Game::GetRenderer() const { return mRenderer; }

	ActorManager* Game::GetActorManager() const { return mActorManager; }

	TexturesManager* Game::GetTexturesManager() const { return mTextureManager; }

	bool Game::InitializeGame()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
		    if(DISPLAY_LOGS)
            {
                SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            }
			return false;
		}

		if (!mRenderer->Initialize())
		{
			return false;
		}

		if (!LoadGame())
		{
			return false;
		}
		mPrevGameTick = SDL_GetTicks();
		mRunning = true;
		return true;
	}

	bool Game::LoadGame()
	{
		if (!mLevelManager->InitLevels())
		{
			return false;
		}
		mActorManager->InitActors();
		return true;
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