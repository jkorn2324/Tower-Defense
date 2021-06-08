#include "Shader.h"

#include <SDL2/SDL.h>
#include <algorithm>
#include <sstream>
#include <fstream>

namespace TowerDefense
{

	Shader::Shader(const std::string& shaderName)
	{
		mLoaded = false;
		mShaderName = shaderName;
		mVertexShader = 0;
		mFragShader = 0;
		mShaderProgram = 0;
		mUniformData = std::vector<ShaderUniformData*>();
	}

	const std::string& Shader::GetShaderName() const
	{
		return mShaderName;
	}

	Shader::~Shader()
	{
		UnLoad();
	}

	void Shader::Bind()
	{
		if (!mLoaded)
		{
			return;
		}
		glUseProgram(mShaderProgram);
	}

	bool Shader::Load(const std::string& vertexShader, const std::string& fragShader)
	{
		if (mLoaded)
		{
			SDL_Log("Shader is already loaded.");
			return true;
		}

		if (!CompileShader(vertexShader, GL_VERTEX_SHADER, mVertexShader)
			|| !CompileShader(fragShader, GL_FRAGMENT_SHADER, mFragShader))
		{
			return false;
		}

		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, mVertexShader);
		glAttachShader(mShaderProgram, mFragShader);
		glLinkProgram(mShaderProgram);
		if (!IsValidProgram())
		{
			return false;
		}

		mLoaded = true;
		return true;
	}

	void Shader::UnLoad()
	{
		if (!mUniformData.empty())
		{
			for (ShaderUniformData* data : mUniformData)
			{
				delete data;
			}
		}
		mUniformData.clear();
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
		std::string contents = shaderString.str();
		const char* shadersChar = contents.c_str();
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
		SDL_Log("Successfully loaded the shader: %s", mShaderName.c_str());
		return true;
	}

	void Shader::SetMatrix4Uniform(const std::string& name, const Matrix4& matrix)
	{
		if (!mLoaded)
		{
			return;
		}
		ShaderUniformData* uniformData = GetUniformData(name);
		glUniformMatrix4fv(uniformData->mLocation, 1, GL_TRUE, matrix.FloatPointer());
	}

	void Shader::SetMatrix3Uniform(const std::string& name, const Matrix3& matrix)
	{
		if (!mLoaded)
		{
			return;
		}
		ShaderUniformData* uniformData = GetUniformData(name);
		glUniformMatrix3fv(uniformData->mLocation, 1, GL_TRUE, matrix.FloatPointer());
	}

	void Shader::SetVec2Uniform(const std::string& name, const Vector2& vec)
	{
		if (!mLoaded)
		{
			return;
		}
		ShaderUniformData* uniformData = GetUniformData(name);
		glUniform2fv(uniformData->mLocation, 1, vec.FloatPointer());
	}

	void Shader::SetVec3Uniform(const std::string& name, const Vector3& vec)
	{
		if (!mLoaded)
		{
			return;
		}
		ShaderUniformData* uniformData = GetUniformData(name);
		glUniform3fv(uniformData->mLocation, 1, vec.FloatPointer());
	}

	void Shader::SetFloatUniform(const std::string& name, float f)
	{
		if (!mLoaded)
		{
			return;
		}
		ShaderUniformData* uniformData = GetUniformData(name);
		glUniform1f(uniformData->mLocation, f);
	}

	ShaderUniformData* Shader::GetUniformData(const std::string& name)
	{
		if (!mLoaded)
		{
			return nullptr;
		}

		const auto& found = std::find_if(mUniformData.begin(), mUniformData.end(),
			[name](ShaderUniformData* uniformData) -> bool
			{
				return uniformData->mUniformName == name;
			});
		if (found != mUniformData.end())
		{
			return *found;
		}
        ShaderUniformData* uniformData = new ShaderUniformData();
		uniformData->mUniformName = name;
		uniformData->mLocation = glGetUniformLocation(mShaderProgram, name.c_str());
		mUniformData.push_back(uniformData);
		return uniformData;
	}
}