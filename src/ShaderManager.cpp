#include "ShaderManager.h"
#include "ShaderManager.h"
#include "ShaderManager.h"
#include "ShaderManager.h"
#include "Shader.h"
#include <SDL2/SDL.h>

namespace TowerDefense
{

	ShaderManager::ShaderManager(class Game* game)
	{
		mGame = game;
		mDefaultShader = nullptr;
		mShaders = std::vector<Shader*>();
	}

	ShaderManager::~ShaderManager()
	{
		for (Shader* shader : mShaders)
		{
			delete shader;
		}
		mShaders.clear();
	}

	Shader* ShaderManager::GetShader(const std::string& name) const
	{
		const auto& searched = std::find_if(mShaders.begin(), mShaders.end(),
			[name](Shader* shader) -> bool 
			{ 
				return shader->GetShaderName() == name;
			});
		if (searched != mShaders.end())
		{
			return *searched;
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
		const auto& searched = std::find_if(mShaders.begin(), mShaders.end(),
			[name](Shader* shader) -> bool
			{
				return shader->GetShaderName() == name;
			});
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
		mShaders.push_back(shader);

		if (defaultShader)
		{
			mDefaultShader = shader;
		}
		return true;
	}
}