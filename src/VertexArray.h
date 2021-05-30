#pragma once

namespace TowerDefense
{
	
	/**
	 * The vertex Array Object. 
     */
	class VertexArray
	{

	public:
		VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices,
			unsigned int numIndices);
		virtual ~VertexArray();

	public:
		void SetTexVerts(const float* verts);
		void Bind();

	protected:
		// Holds the buffer for the vertex coordinates.
		unsigned int mVertexBuffer;

	private:
		unsigned int mNumVertices;
		unsigned int mIndexBuffer;
		unsigned int mNumIndices;
		// The vertex array.
		unsigned int mVertexArray;

	protected:
		const unsigned int NUM_VERTEX_INDICES = 3;
		const unsigned int NUM_UV_INDICES = 2;
	};
}