#include "GLBuffers.h"

#include <GL/glew.h>
#include <SDL2/SDL_log.h>

namespace TowerDefense
{

	// ------------------ The Vertex Buffer Data Structure ----------------------

	VertexBuffer::VertexBuffer(unsigned int numVerts)
	{
		mStatic = false;
		mNumVerts = numVerts;
		mLayout = BufferAttributeLayout();

		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
	}
	
	VertexBuffer::VertexBuffer(const float* verts, unsigned int sizeOfVerts, unsigned int numVerts)
	{
		mStatic = false;
		mNumVerts = numVerts;
		mLayout = BufferAttributeLayout();

		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVerts, verts, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(const float* verts, unsigned int sizeOfVerts, unsigned int numVerts, bool isStatic)
	{
		mStatic = isStatic;
		mNumVerts = numVerts;
		mLayout = BufferAttributeLayout();

		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVerts, verts, 
			mStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}
	
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mBufferID);
	}
	
	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
	}
	
	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetVertices(const float* verts, unsigned int sizeOfVerts, unsigned int numVerts)
	{
		if (mStatic)
		{
			return;
		}

		mNumVerts = numVerts;
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfVerts, reinterpret_cast<const void*>(verts));
	}

	bool VertexBuffer::IsStatic() const
	{
		return mStatic;
	}

	void VertexBuffer::SetLayout(std::initializer_list<BufferAttribute> layout)
	{
		mLayout.SetAttributes(layout);
	}

	const BufferAttributeLayout& VertexBuffer::GetLayout() const
	{
		return mLayout;
	}

	// ---------------------------- The Index Buffer Data Structure -----------------------


	IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int numIndices)
	{
		mNumIndices = numIndices;

		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int),
			indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mBufferID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}