#include "ShaderManager.h"

#include "Shader.h"
#include <SDL2/SDL.h>
#include <algorithm>

namespace TowerDefense
{

	ShaderManager::ShaderManager(class Game* game)
	{
		mGame = game;
		mDefaultShader = nullptr;
		mShaders = std::unordered_map<std::string, Shader*>();
	}

	ShaderManager::~ShaderManager()
	{
		for (const auto& shaderPair : mShaders)
		{
		    Shader* shader = shaderPair.second;
			delete shader;
		}
		mShaders.clear();
	}

	Shader* ShaderManager::GetShader(const std::string& name) const
	{
		const auto& searched = mShaders.find(name);
		if (searched != mShaders.end())
		{
			return (*searched).second;
		}
		return nullptr;
	}

	Shader* ShaderManager::GetDefaultShader() const
	{
		return mDefaultShader;
	}

	void ShaderManager::SetDefaultShader(Shader* shader)
	{
		mDefaultShader = shader;
	}

	bool ShaderManager::AddShader(const std::string& name, const std::string& fragFile, const std::string& vertFile, bool defaultShader)
	{
		const auto& searched = mShaders.find(name);
		if (searched != mShaders.end())
		{
			SDL_Log("Shader %s already exists.", name.c_str());
			return true;
		}

		Shader* shader = new Shader(name);
		if (!shader->Load(vertFile, fragFile))
		{
			delete shader;
			return false;
		}
		mShaders.emplace(name, shader);
		if (defaultShader)
		{
			mDefaultShader = shader;
		}
		return true;
	}
}