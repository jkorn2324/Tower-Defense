#pragma once

namespace TowerDefense
{
	
	/**
	 * The vertex Array Object. 
     */
	class VertexArray
	{

	public:
		VertexArray(const float* verts, const float* texVerts, unsigned int numVerts, 
			const unsigned int* indicies, unsigned int numIndicies);
		virtual ~VertexArray();

	public:
		void SetTexVerts(const float* verts);
		void Bind();

	protected:
		// Holds the buffer for the vertex coordinates.
		unsigned int mVertexBuffer;
		// Holds the buffer for the texture coordinates.
		unsigned int mTexBuffer;

	private:
		unsigned int mNumVertices;
		unsigned int mIndexBuffer;
		unsigned int mNumIndices;

	private:
		// The tex vert array.
		unsigned int mTexVertArray;
		// The vertex array.
		unsigned int mVertexArray;

	protected:
		const unsigned int NUM_VERTEX_INDICES = 3;
		const unsigned int NUM_UV_INDICES = 2;
	};
}