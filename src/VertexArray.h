#pragma once

namespace TowerDefense
{
	
	/**
	 * The vertex Array Object. 
     */
	class VertexArray
	{

	public:
		VertexArray(const float* verts, unsigned int numVerts);
		virtual ~VertexArray();

	public:
		void Bind();

	public:
		void SetIndexBuffer(class IndexBuffer* indexBuffer);

	protected:
		// Holds the buffer for the vertex coordinates.
		unsigned int mVertexBuffer;

	private:
		unsigned int mNumVertices;
		// The vertex array.
		unsigned int mVertexArray;

	private:
		class IndexBuffer* mIndexBuffer;

	protected:
		const unsigned int NUM_VERTEX_INDICES = 3;
		const unsigned int NUM_UV_INDICES = 2;
	};
}