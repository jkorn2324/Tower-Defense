#pragma once

#include <string>
#include <vector>

#include <gl/glew.h>

namespace TowerDefense
{
	
	enum class ShaderDataType
	{
		NONE, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL
	};

	unsigned int GetShaderDataTypeSize(const ShaderDataType& dataType);
	GLenum ShaderDataTypeToGLEnum(const ShaderDataType& dataType);

	// The Buffer Attribute.
	struct BufferAttribute
	{
	public:
		BufferAttribute();
		BufferAttribute(ShaderDataType type, const std::string& name, bool normalized = false);

	public:
		unsigned int GetNumComponents() const;

	public:
		ShaderDataType shaderDataType;
		unsigned int size;
		unsigned int offset;
		std::string name;
		bool normalized;
	};

	// The Buffer Attribute layout class.
	class BufferAttributeLayout
	{
	public:
		BufferAttributeLayout();
		BufferAttributeLayout(std::initializer_list<BufferAttribute> attributes);

	public:
		unsigned int GetStride() const;

	public:
		void SetAttributes(std::initializer_list<BufferAttribute> attributes);
		void AddAttribute(const std::string& name, const ShaderDataType& dataType, bool normalized = false);
		const std::vector<BufferAttribute>& GetAttributes() const;
		std::vector<BufferAttribute>::const_iterator begin() const;
		std::vector<BufferAttribute>::const_iterator end() const;
		std::vector<BufferAttribute>::iterator begin();
		std::vector<BufferAttribute>::iterator end();

	private:
		void CalculateOffsetsAndStride();

	private:
		unsigned int mStride;
		std::vector<BufferAttribute> mAttributes;
	};
}