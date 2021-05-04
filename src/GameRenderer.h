#pragma once

#include <SDL2/SDL.h>
#include "Matrix4.h"
#include <string>

namespace TowerDefense
{

	class GameRenderer
	{

	public:
		GameRenderer(class Game* game);

	public:
		bool Initialize();
		void Render();
		void Uninitialize();

	public:
		unsigned int GetWindowSizeX() const;
		unsigned int GetWindowSizeY() const;

	private:
		class Game* mGame;
		SDL_Window* mWindow;
		SDL_GLContext mGLContext;

	private:
		unsigned int mWindowSizeX, mWindowSizeY;
		std::string mWindowName;

	private:
		Matrix4 mViewProjection;
	};
}