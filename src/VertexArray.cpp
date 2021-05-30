#include "VertexArray.h"

#include <memory>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace TowerDefense
{

	VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
	{
		mNumVertices = numVerts;
		mNumIndices = numIndices;

		// Generates vertex array.
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);
		// Holds the vertex buffer.
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, numVerts * (NUM_VERTEX_INDICES 
			+ NUM_UV_INDICES) * sizeof(float), verts, GL_STATIC_DRAW);
		// Generates the index buffer.
		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int),
			indices, GL_STATIC_DRAW);
		// Sets up the vertex coords.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
			sizeof(float) * (NUM_VERTEX_INDICES + NUM_UV_INDICES), 0);
		// Sets up the texture coords.
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(float) * NUM_UV_INDICES, reinterpret_cast<void*>(
				sizeof(float) * NUM_VERTEX_INDICES));
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteVertexArrays(1, &mVertexArray);
	}

	void VertexArray::SetTexVerts(const float* verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 
			NUM_VERTEX_INDICES + 1, mNumVertices * NUM_UV_INDICES * sizeof(float), verts);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(mVertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	}
}