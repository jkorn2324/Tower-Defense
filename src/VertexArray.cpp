#include "VertexArray.h"
#include "GLBuffers.h"
#include "GLBufferAttribute.h"

#include <memory>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace TowerDefense
{

	VertexArray::VertexArray()
	{
		mIndexBuffer = nullptr;
		mVertexBufferIndex = 0;
		mVertexBuffers = std::vector<VertexBuffer*>();

		// Generates vertex array.
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &mVertexArray);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(mVertexArray);
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		mIndexBuffer = indexBuffer;
	}

	void VertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
	{
		if (vertexBuffer == nullptr 
			|| vertexBuffer->GetLayout().GetAttributes().size() <= 0)
		{
			return;
		}

		Bind();
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.shaderDataType)
			{
				case ShaderDataType::FLOAT:
				case ShaderDataType::FLOAT2:
				case ShaderDataType::FLOAT3:
				case ShaderDataType::FLOAT4:
				{
					glEnableVertexAttribArray(mVertexBufferIndex);
					glVertexAttribPointer(mVertexBufferIndex,
						element.GetNumComponents(),
						ShaderDataTypeToGLEnum(element.shaderDataType),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						reinterpret_cast<void*>(element.offset));
					mVertexBufferIndex++;
					break;
				}
				case ShaderDataType::INT:
				case ShaderDataType::INT2:
				case ShaderDataType::INT3:
				case ShaderDataType::INT4:
				{	
					glEnableVertexAttribArray(mVertexBufferIndex);
					glVertexAttribIPointer(mVertexBufferIndex,
						element.GetNumComponents(),
						ShaderDataTypeToGLEnum(element.shaderDataType),
						layout.GetStride(),
						reinterpret_cast<void*>(element.offset));
					mVertexBufferIndex++;
					break;
				}
				case ShaderDataType::MAT3:
				case ShaderDataType::MAT4:
				{
					uint8_t componentNum = element.GetNumComponents();
					for (uint8_t i = 0; i < componentNum; i++)
					{
						glEnableVertexAttribArray(mVertexBufferIndex);
						glVertexAttribPointer(mVertexBufferIndex,
							componentNum,
							ShaderDataTypeToGLEnum(element.shaderDataType),
							element.normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							reinterpret_cast<void*>(element.offset + sizeof(float) * componentNum * i));
						glVertexAttribDivisor(mVertexBufferIndex, 1);
						mVertexBufferIndex++;
					}
					break;
				}
			}
		}
		mVertexBuffers.push_back(vertexBuffer);
	}
}