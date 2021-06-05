#pragma once

namespace TowerDefense
{

	/**
	 * The Vertex Buffer Definition. 
	 */
	class VertexBuffer
	{

	public:
		VertexBuffer(unsigned int numVerts);
		VertexBuffer(const float* verts, unsigned int numVerts);
		VertexBuffer(const float* verts, unsigned int numVerts, bool isStatic);
		~VertexBuffer();

	public:
		void Bind();
		void UnBind();
		void SetVertices(const float* verts, unsigned int numVerts);
		bool IsStatic() const;

	private:
		bool mStatic;
		unsigned int mBufferID;
		unsigned int mNumVerts;
	};

	/**
	 * The Index Buffer Definition. 
	 */
	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* indices, unsigned int numIndices);
		~IndexBuffer();

	public:
		void Bind();
		void UnBind();

	private:
		unsigned int mBufferID;
		unsigned int mNumIndices;
	};
}