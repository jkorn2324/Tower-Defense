#include "Game.h"
#include "GameRenderer.h"
#include "ActorManager.h"
#include "LevelManager.h"
#include "TexturesManager.h"
#include "GameParameters.h"
#include "JSONHelper.h"
#include "Mouse.h"
#include "Camera.h"
#include "MixChunkAudioManager.h"

namespace TowerDefense
{

	Game::Game()
	{
        mCamera = new Camera(static_cast<float>(WINDOW_SIZE_X),
                             static_cast<float>(WINDOW_SIZE_Y));
		mRenderer = new GameRenderer(this);
		mActorManager = new ActorManager(this);
		mTextureManager = new TexturesManager(this);
		mLevelManager = new LevelManager(this);
		mMouse = new Mouse(this);
		mMixChunkAudioManager = new MixChunkAudioManager();
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

	Mouse* Game::GetMouse() const { return mMouse; }

	Camera* Game::GetCamera() const { return mCamera; }

	MixChunkAudioManager* Game::GetMixChunkAudioManager() const { return mMixChunkAudioManager; }

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

		if(!mMouse->Initialize())
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
				case SDL_MOUSEBUTTONDOWN:
			        mMouse->OnMouseDown(event.button);
			        break;
			    case SDL_MOUSEBUTTONUP:
			        mMouse->OnMouseUp(event.button);
			        break;
			    case SDL_MOUSEMOTION:
			        mMouse->OnMouseMove(event.motion);
			        break;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(nullptr);
		mActorManager->ProcessInput(state);
	}

	void Game::UpdateGame()
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mPrevGameTick + WAIT_TIME_TICKS));
		Uint32 currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - mPrevGameTick) / 1000.0f;
		mActorManager->Update(deltaTime);
		mLevelManager->Update(deltaTime);
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
		delete mRenderer, mActorManager, mTextureManager,
		    mMouse, mLevelManager, mCamera, mMixChunkAudioManager;
	}
}