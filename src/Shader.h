#pragma once

#include <string>
#include <GL/glew.h>

namespace TowerDefense
{

	class Shader
	{

	public:
		Shader();
		~Shader();

	public:
		void SetActiveShader();
		void UnLoad();
		bool Load(const std::string& vertFile, const std::string& fragFile);

	private:
		bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
		bool IsCompiled(GLuint shader);
		bool IsValidProgram();

	private:
		GLuint mVertexShader;
		GLuint mFragShader;
		GLuint mShaderProgram;
	};
}