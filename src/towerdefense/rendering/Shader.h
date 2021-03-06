#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>

#include "Matrix4.h"
#include "Matrix3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

namespace TowerDefense
{

	struct ShaderUniformData
	{
		std::string mUniformName;
		GLuint mLocation;
	};

	class Shader
	{

	public:
		Shader(const std::string& name);
		~Shader();

	public:
		const std::string& GetShaderName() const;

	public:
		void Bind();
		void UnLoad();
		bool Load(const std::string& vertFile, const std::string& fragFile);

	public:
		void SetMatrix4Uniform(const std::string& name, const Matrix4& matrix);
		void SetMatrix3Uniform(const std::string& name, const Matrix3& matrix);
		void SetVec2Uniform(const std::string& name, const Vector2& vec);
		void SetVec3Uniform(const std::string& name, const Vector3& vec);
		void SetVec4Uniform(const std::string& name, const Color& color);
		void SetFloatUniform(const std::string& name, float f);

	private:
		bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
		bool IsCompiled(GLuint shader);
		bool IsValidProgram();

	private:
		ShaderUniformData* GetUniformData(const std::string& name);

	private:
		GLuint mVertexShader;
		GLuint mFragShader;
		GLuint mShaderProgram;

	private:
		std::vector<ShaderUniformData*> mUniformData;
		bool mLoaded;
		std::string mShaderName;
	};
}