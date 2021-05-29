#pragma once

#include <SDL2/SDL.h>
#include "Matrix4.h"
#include <vector>
#include <string>

namespace TowerDefense
{

	class GameRenderer
	{

	public:
		GameRenderer(class Game* game);
		~GameRenderer();

	public:
		bool Initialize();
		void Render();
		void Uninitialize();

	public:
		void AddSpriteComponent(class SpriteComponent* spriteComponent);
		void RemoveSpriteComponent(class SpriteComponent* spriteComponent);

	public:
		class VertexArrayManager* GetVertexArrayManager() const;
		class ShaderManager* GetShaderManager() const;
		unsigned int GetWindowSizeX() const;
		unsigned int GetWindowSizeY() const;


	private:
		void LoadSpriteVertices();
		void LoadShaders();

	private:
		class Game* mGame;
		SDL_Window* mWindow;
		SDL_GLContext mGLContext;

	private:
		class ShaderManager* mShaderManager;
		class VertexArrayManager* mVertexArrayManager;
		std::vector<class SpriteComponent*> mSpriteComponents;

	private:
		unsigned int mWindowSizeX, mWindowSizeY;
		std::string mWindowName;

	private:
		Matrix4 mViewProjection;
	};
}