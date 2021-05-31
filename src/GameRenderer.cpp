#include "GameRenderer.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Game.h"
#include "GameParameters.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"

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
		mSpriteComponents = std::vector<SpriteComponent*>();
		mShaderManager = new ShaderManager(game);
		mDefaultVertexArray = nullptr;
		mViewProjection = Matrix4::CreateSimpleViewProjection(
			mWindowSizeX, mWindowSizeY);
	}

	GameRenderer::~GameRenderer()
	{
		mSpriteComponents.clear();
		delete mDefaultVertexArray;
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
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			mWindowSizeX, mWindowSizeY, SDL_WINDOW_OPENGL);
		if (mWindow == nullptr)
		{
			SDL_Log("Failed to create SDL Window. Error: %s", SDL_GetError());
			return false;
		}
		mGLContext = SDL_GL_CreateContext(mWindow);
		SDL_GL_SetSwapInterval(1);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLEW.");
			return false;
		}
		glGetError();
		if (!LoadShaders())
		{
			return false;
		}
		LoadSpriteVertices();
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

	const Matrix4& GameRenderer::GetViewProjectionMatrix() const
	{
		return mViewProjection;
	}

	ShaderManager* GameRenderer::GetShaderManager() const
	{
		return mShaderManager;
	}

	void GameRenderer::AddSpriteComponent(SpriteComponent* spriteComponent)
	{
		mSpriteComponents.push_back(spriteComponent);
	}

	void GameRenderer::RemoveSpriteComponent(SpriteComponent* spriteComponent)
	{
		const auto& spriteSearched = std::find(mSpriteComponents.begin(), 
			mSpriteComponents.end(), spriteComponent);
		mSpriteComponents.erase(spriteSearched);
	}

	VertexArray* GameRenderer::GetDefaultVertexArray() const
	{
		return mDefaultVertexArray;
	}

	bool GameRenderer::LoadShaders()
	{
		if (!mShaderManager->AddShader("sprite",
			"Assets/Shaders/Sprite.frag", "Assets/Shaders/Sprite.vert", true))
		{
			return false;
		}

		Shader* spriteShader = mShaderManager->GetShader("sprite");
		spriteShader->SetMatrix4Uniform("uViewProjection", mViewProjection);
		return true;
	}

	void GameRenderer::LoadSpriteVertices()
	{
		float vertices[] =
		{
			-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = 
		{
			0, 1, 2,
			2, 3, 0
		};
		mDefaultVertexArray = new VertexArray(vertices, 4, indices, 6);
	}

	void GameRenderer::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		for (SpriteComponent* spriteComponent : mSpriteComponents)
		{
			spriteComponent->Draw();
		}
		glDisable(GL_BLEND);
		SDL_GL_SwapWindow(mWindow);
	}
}