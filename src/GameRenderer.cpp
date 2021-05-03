#include "GameRenderer.h"
#include "Game.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "GameParameters.h"

namespace TowerDefense
{

	GameRenderer::GameRenderer(Game* game)
	{
		mWindow = nullptr;
		mGLContext = SDL_GLContext();
		mGame = game;
		mWindowSizeX = WINDOW_SIZE_X;
		mWindowSizeY = WINDOW_SIZE_Y;
		mWindowName = WINDOW_NAME;
	}

	bool GameRenderer::Initialize()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		mWindow = SDL_CreateWindow(mWindowName.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowSizeX, mWindowSizeY, SDL_WINDOW_OPENGL);
		if (mWindow == nullptr)
		{
			SDL_Log("Failed to create SDL Window. Error: %s", SDL_GetError());
			return false;
		}

		mGLContext = SDL_GL_CreateContext(mWindow);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLEW.");
			return false;
		}

		glGetError();
		return true;
	}

	void GameRenderer::Uninitialize()
	{
		SDL_GL_DeleteContext(mGLContext);
		SDL_DestroyWindow(mWindow);
	}

	unsigned int GameRenderer::GetWindowSizeX() const
	{
		return mWindowSizeX;
	}

	unsigned int GameRenderer::GetWindowSizeY() const
	{
		return mWindowSizeY;
	}

	void GameRenderer::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: Draw Scene

		SDL_GL_SwapWindow(mWindow);
	}
}