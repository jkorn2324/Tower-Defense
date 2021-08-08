#pragma once

#include <SDL2/SDL.h>

namespace TowerDefense
{


	class Game
	{
	public:
		Game();
		~Game() = default;

	public:
		bool InitializeGame();
		void RunGame();
		void ShutdownGame();

	private:
		bool LoadGame();
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();

	public:
		class LevelManager* GetLevelManager() const;
		class GameRenderer* GetRenderer() const;
		class ActorManager* GetActorManager() const;
		class TexturesManager* GetTexturesManager() const;
        class Mouse* GetMouse() const;
        class Camera* GetCamera() const;
        class MixChunkAudioManager* GetMixChunkAudioManager() const;

	private:
		bool mRunning;
		Uint32 mPrevGameTick;

	private:
		class GameRenderer* mRenderer;
		class TexturesManager* mTextureManager;
		class ActorManager* mActorManager;
		class LevelManager* mLevelManager;
		class MixChunkAudioManager* mMixChunkAudioManager;
		class Mouse* mMouse;
		class Camera* mCamera;
	};
}