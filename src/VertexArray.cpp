#include "VertexArray.h"
#include "GLBuffers.h"

#include <memory>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace TowerDefense
{

	VertexArray::VertexArray(const float* verts, unsigned int numVerts)
	{
		mNumVertices = numVerts;
		mIndexBuffer = nullptr;

		// Generates vertex array.
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);
		// Holds the vertex buffer (VBO).
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, numVerts * (NUM_VERTEX_INDICES 
			+ NUM_UV_INDICES) * sizeof(float), verts, GL_STATIC_DRAW);
		// Sets up the vertex coords.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
			sizeof(float) * (NUM_VERTEX_INDICES + NUM_UV_INDICES), 0);
		// Sets up the texture coords.
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(float) * (NUM_VERTEX_INDICES + NUM_UV_INDICES), 
			reinterpret_cast<void*>(sizeof(float) * NUM_VERTEX_INDICES));
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &mVertexBuffer);
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
}