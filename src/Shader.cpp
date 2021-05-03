#include "Shader.h"
#include <SDL2/SDL.h>
#include <sstream>
#include <fstream>

namespace TowerDefense
{

	Shader::Shader()
	{
		mVertexShader = 0;
		mFragShader = 0;
		mShaderProgram = 0;
	}

	Shader::~Shader()
	{
		UnLoad();
	}

	void Shader::SetActiveShader()
	{
		glUseProgram(mShaderProgram);
	}

	bool Shader::Load(const std::string& vertexShader, const std::string& fragShader)
	{
		if (!CompileShader(vertexShader, GL_VERTEX_SHADER, mVertexShader)
			|| !CompileShader(fragShader, GL_FRAGMENT_SHADER, mFragShader))
		{
			return false;
		}

		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, mVertexShader);
		glAttachShader(mShaderProgram, mFragShader);
		glLinkProgram(mShaderProgram);
		return IsValidProgram();
	}

	void Shader::UnLoad()
	{
		glDeleteProgram(mShaderProgram);
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragShader);
	}

	bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
	{
		std::ifstream shaderFile(fileName);
		if (shaderFile.fail() || !shaderFile.is_open())
		{
			SDL_Log("Shader file not found: %s", fileName.c_str());
			return false;
		}

		std::stringstream shaderString;
		shaderString << shaderFile.rdbuf();
		char* shadersChar = (char*)shaderString.str().c_str();
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(shadersChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}

		return true;
	}

	bool Shader::IsCompiled(GLuint shader)
	{
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetShaderInfoLog(shader, 511, nullptr, buffer);
			SDL_Log("GLSL Compile Shader Failed: \n%s", buffer);
			return false;
		}
		return true;
	}

	bool Shader::IsValidProgram()
	{
		GLint status;
		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
			SDL_Log("GLSL Program Failed: \n%s", buffer);
			return false;
		}
		return true;
	}
}