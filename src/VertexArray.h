#pragma once

namespace TowerDefense
{

	class VertexArray
	{

	public:
		VertexArray(const float* verts, unsigned int numVerts, 
			const unsigned int* indicies, unsigned int numIndicies);
		~VertexArray();

	public:
		void Bind();

	private:
		unsigned int mVertexBuffer;
		unsigned int mNumVertices;
		unsigned int mIndexBuffer;
		unsigned int mNumIndices;
		unsigned int mVertexArray;
	};
}