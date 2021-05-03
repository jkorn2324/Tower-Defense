#include "VertexArray.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace TowerDefense
{

	VertexArray::VertexArray(const float* vertices, unsigned int numVerts,
		const unsigned int* indicies, unsigned int numIndicies)
	{
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(float), 
			vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(unsigned int),
			indicies, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

		mNumVertices = numVerts;
		mNumIndices = numIndicies;
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteVertexArrays(1, &mVertexArray);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(mVertexArray);
	}
}