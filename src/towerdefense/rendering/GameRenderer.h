#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Matrix4.h"
#include "Vector2.h"

namespace TowerDefense
{

	class GameRenderer
	{

	public:
		explicit GameRenderer(class Game* game);
		~GameRenderer();

	public:
		bool Initialize();
		void Render();
		void Uninitialize();

	public:
	    void ReOrderSpriteComponents();
		void AddSpriteComponent(class SpriteComponent* spriteComponent);
		void RemoveSpriteComponent(class SpriteComponent* spriteComponent);

	public:
        void ReOrderUIImageComponents();
        void AddUIImageComponent(class UIImageComponent* imageComponent);
        void RemoveUIImageComponent(class UIImageComponent* imageComponent);

	public:
	    Vector2 ScreenToWorldPoint(const Vector2& screenCoord);
	    Vector2 WorldToScreenPoint(const Vector2& worldCoord);

	public:
		class VertexArray* GetDefaultVertexArray() const;
		class VertexBuffer* GetDefaultUVBuffer() const;
		class ShaderManager* GetShaderManager() const;
		unsigned int GetWindowSizeX() const;
		unsigned int GetWindowSizeY() const;
		Vector2 GetWindowSize() const;
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
		std::vector<class UIImageComponent*> mUIImageComponents;

	private:
		unsigned int mWindowSizeX, mWindowSizeY;
		std::string mWindowName;

	private:
		Matrix4 mViewProjection;
	};
}