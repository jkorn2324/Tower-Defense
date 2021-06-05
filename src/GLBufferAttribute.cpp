#include "GLBufferAttribute.h"

#include <SDL2/SDL_log.h>

namespace TowerDefense
{
	unsigned int GetShaderDataTypeSize(const ShaderDataType& dataType)
	{
		switch (dataType)
		{
			case ShaderDataType::BOOL:
				return sizeof(bool);
			case ShaderDataType::FLOAT:
				return sizeof(float);
			case ShaderDataType::FLOAT2:
				return sizeof(float) * 2;
			case ShaderDataType::FLOAT3:
				return sizeof(float) * 3;
			case ShaderDataType::FLOAT4:
				return sizeof(float) * 4;
			case ShaderDataType::INT:
				return sizeof(int);
			case ShaderDataType::INT2:
				return sizeof(int) * 2;
			case ShaderDataType::INT3:
				return sizeof(int) * 3;
			case ShaderDataType::INT4:
				return sizeof(int) * 4;
			case ShaderDataType::MAT3:
				return sizeof(float) * 4 * 3;
			case ShaderDataType::MAT4:
				return sizeof(float) * 4 * 4;
		}

		SDL_Log("Unknown Shader Data Type");
		return 0;
	}

	GLenum ShaderDataTypeToGLEnum(const ShaderDataType& dataType)
	{
		switch (dataType)
		{
			case ShaderDataType::BOOL:
				return GL_BOOL;
			case ShaderDataType::FLOAT:
			case ShaderDataType::FLOAT2:
			case ShaderDataType::FLOAT3:
			case ShaderDataType::FLOAT4:
			case ShaderDataType::MAT3:
			case ShaderDataType::MAT4:
				return GL_FLOAT;
			case ShaderDataType::INT:
			case ShaderDataType::INT2:
			case ShaderDataType::INT3:
			case ShaderDataType::INT4:
				return GL_INT;
		}
		
		SDL_Log("Unknown Shader Data Type");
		return 0;
	}

	BufferAttribute::BufferAttribute()
	{
		shaderDataType = ShaderDataType::NONE;
		name = "Unknown";
		normalized = false;
		size = GetShaderDataTypeSize(shaderDataType);
		offset = 0;
	}

	BufferAttribute::BufferAttribute(ShaderDataType type, const std::string& name, bool normalized)
	{
		this->shaderDataType = type;
		this->name = name;
		this->normalized = normalized;
		this->size = GetShaderDataTypeSize(type);
		this->offset = 0;
	}

	unsigned int BufferAttribute::GetNumComponents() const
	{
		switch (shaderDataType)
		{
			case ShaderDataType::BOOL:
				return 1;
			case ShaderDataType::FLOAT:
				return 1;
			case ShaderDataType::FLOAT2:
				return 2;
			case ShaderDataType::FLOAT3:
				return 3;
			case ShaderDataType::FLOAT4:
				return 4;
			case ShaderDataType::INT:
				return 1;
			case ShaderDataType::INT2:
				return 2;
			case ShaderDataType::INT3:
				return 3;
			case ShaderDataType::INT4:
				return 4;
			case ShaderDataType::MAT3:
				return 3;
			case ShaderDataType::MAT4:
				return 4;
		}

		SDL_Log("Unknown Shader Data Type");
		return 0;
	}

	BufferAttributeLayout::BufferAttributeLayout()
	{
		mStride = 0;
		mAttributes = std::vector<BufferAttribute>();
	}

	BufferAttributeLayout::BufferAttributeLayout(std::initializer_list<BufferAttribute> attributes)
	{
		mStride = 0;
		mAttributes = attributes;
		CalculateOffsetsAndStride();
	}

	void BufferAttributeLayout::CalculateOffsetsAndStride()
	{
		mStride = 0;

		for (auto& a : mAttributes)
		{
			a.offset = mStride;
			mStride += a.size;
		}
	}

	void BufferAttributeLayout::SetAttributes(std::initializer_list<BufferAttribute> attributes)
	{
		mAttributes = attributes;
		CalculateOffsetsAndStride();
	}

	void BufferAttributeLayout::AddAttribute(const std::string& name, const ShaderDataType& type, bool normalized)
	{
		const auto& foundIterator = std::find_if(mAttributes.begin(), mAttributes.end(),
			[name](BufferAttribute attribute) -> bool
			{
				return name == attribute.name;
			});
		if (foundIterator != mAttributes.end())
		{
			return;
		}
		BufferAttribute attribute(type, name, normalized);
		mAttributes.push_back(attribute);
	}

	unsigned int BufferAttributeLayout::GetStride() const
	{
		return mStride;
	}
	
	const std::vector<BufferAttribute>& BufferAttributeLayout::GetAttributes() const
	{
		return mAttributes;
	}
	
	std::vector<BufferAttribute>::const_iterator BufferAttributeLayout::begin() const
	{
		return mAttributes.begin();
	}
	
	std::vector<BufferAttribute>::const_iterator BufferAttributeLayout::end() const
	{
		return mAttributes.end();
	}
	
	std::vector<BufferAttribute>::iterator BufferAttributeLayout::begin()
	{
		return mAttributes.begin();
	}
	
	std::vector<BufferAttribute>::iterator BufferAttributeLayout::end()
	{
		return mAttributes.end();
	}
}