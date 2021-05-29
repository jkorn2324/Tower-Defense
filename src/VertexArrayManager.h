#pragma once

#include <unordered_map>
#include <string>

namespace TowerDefense
{

	class Vector2;

	class VertexArrayManager
	{
	public:
		VertexArrayManager();
		~VertexArrayManager();

	public:
		class VertexArray* CreateVertexArray(const std::string& name, const float* verts,
			const float* texVerts, unsigned int vertSize, const unsigned int* indices, unsigned int indicesSize);
		class VertexArray* CreateSpriteVertexArray(const std::string& name, const Vector2& spriteSize, const Vector2& minTexPos, const Vector2& maxTexPos);
		
	public:
		void SetDefaultVertexArray(class VertexArray* vertexArray);
		class VertexArray* GetDefaultVertexArray() const;
		class VertexArray* GetVertexArray(const std::string& name) const;

	private:
		class VertexArray* mDefaultVertexArray;
		std::unordered_map<std::string, class VertexArray*> mVertexArrays;
	};
}