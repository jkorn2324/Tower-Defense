#pragma once

#include <string>
#include <unordered_map>

namespace TowerDefense
{


	class ShaderManager
	{
	public:
		ShaderManager(class Game* game);
		~ShaderManager();

	public:
		class Shader* GetShader(const std::string& name) const;
		class Shader* GetDefaultShader() const;

	private:
		void SetDefaultShader(class Shader* shader);
		bool AddShader(const std::string& name, const std::string& fragFile, const std::string& vertFile, bool defaultShader = false);

	private:
		class Game* mGame;

	private:
	    std::unordered_map<std::string, class Shader*> mShaders;
		Shader* mDefaultShader;

		friend class GameRenderer;
	};
}