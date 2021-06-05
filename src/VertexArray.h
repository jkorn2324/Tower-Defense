#pragma once

#include <vector>

namespace TowerDefense
{

	/**
	 * The vertex Array Object. 
     */
	class VertexArray
	{

	public:
		VertexArray();
		virtual ~VertexArray();

	public:
		void Bind();

	public:
		void SetIndexBuffer(class IndexBuffer* indexBuffer);
		void AddVertexBuffer(class VertexBuffer* vertexBuffer);

	private:
		std::vector<class VertexBuffer*> mVertexBuffers;
		unsigned int mVertexBufferIndex;

	private:
		// The vertex array.
		unsigned int mVertexArray;
		class IndexBuffer* mIndexBuffer;

	protected:
		const unsigned int NUM_VERTEX_INDICES = 3;
		const unsigned int NUM_UV_INDICES = 2;
	};
}