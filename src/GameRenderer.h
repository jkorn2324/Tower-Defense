#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Matrix4.h"

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
		class VertexArray* GetDefaultVertexArray() const;
		class VertexBuffer* GetDefaultUVBuffer() const;
		class ShaderManager* GetShaderManager() const;
		unsigned int GetWindowSizeX() const;
		unsigned int GetWindowSizeY() const;
		const Matrix4& GetViewProjectionMatrix() const;

	private:
		void LoadSpriteVertices();
		void SetDefaultUVs();
		bool LoadShaders();

	private:
		class Game* mGame;
		SDL_Window* mWindow;
		SDL_GLContext mGLContext;

	private:
		class IndexBuffer* mDefaultIndexBuffer;
		class VertexBuffer* mDefaultVertexBuffer;
		class VertexBuffer* mDefaultUVBuffer;
		class VertexArray* mDefaultVertexArray;

	private:
		class ShaderManager* mShaderManager;
		std::vector<class SpriteComponent*> mSpriteComponents;

	private:
		unsigned int mWindowSizeX, mWindowSizeY;
		std::string mWindowName;

	private:
		Matrix4 mViewProjection;
	};
}