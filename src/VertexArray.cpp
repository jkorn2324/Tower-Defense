#include "VertexArray.h"

#include <memory>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace TowerDefense
{

	VertexArray::VertexArray(const float* vertices, const float* texVertices, unsigned int numVerts,
		const unsigned int* indicies, unsigned int numIndicies)
	{
		// Generates vertex array.
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);
		glGenBuffers(1, &mVertexBuffer);
		// Generates tex vertex array.
		glGenVertexArrays(1, &mTexVertArray);
		glBindVertexArray(mTexVertArray);
		glGenBuffers(1, &mTexBuffer);
		// Holds the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, numVerts * NUM_VERTEX_INDICES * sizeof(float),
			vertices, GL_STATIC_DRAW);
		// Holds the tex coord buffer.
		glBindBuffer(GL_ARRAY_BUFFER, mTexBuffer);
		glBufferData(GL_ARRAY_BUFFER, numVerts * NUM_UV_INDICES * sizeof(float), 
			texVertices, GL_DYNAMIC_DRAW);
		// Generates the index buffer.
		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(unsigned int),
			indicies, GL_STATIC_DRAW);
		// Sets up the vertex coords.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_VERTEX_INDICES, 0);
		// Sets up the texture coords.
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(float) * NUM_UV_INDICES, reinterpret_cast<void*>(sizeof(float) * NUM_VERTEX_INDICES));
		mNumVertices = numVerts;
		mNumIndices = numIndicies;
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteVertexArrays(1, &mVertexArray);
	}

	void VertexArray::SetTexVerts(const float* verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mTexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, mNumVertices * NUM_UV_INDICES * sizeof(float), verts);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(mVertexArray);
	}
}