#include "VertexArrayManager.h"
#include "VertexArray.h"

namespace TowerDefense
{

	VertexArrayManager::VertexArrayManager()
	{
		mDefaultVertexArray = nullptr;
		mVertexArrays = std::unordered_map<std::string, VertexArray*>();
	}

	VertexArrayManager::~VertexArrayManager()
	{
		for (const auto& pair : mVertexArrays)
		{
			VertexArray* vertexArray = pair.second;
			if (vertexArray != nullptr)
			{
				delete vertexArray;
			}
		}
		if (mDefaultVertexArray != nullptr)
		{
			delete mDefaultVertexArray;
		}
		mVertexArrays.clear();
	}

	void VertexArrayManager::SetDefaultVertexArray(VertexArray* arr)
	{
		if (mDefaultVertexArray != nullptr)
		{
			delete mDefaultVertexArray;
		}
		mDefaultVertexArray = arr;
	}

	VertexArray* TowerDefense::VertexArrayManager::GetDefaultVertexArray() const
	{
		return mDefaultVertexArray;
	}

	VertexArray* TowerDefense::VertexArrayManager::CreateVertexArray(const std::string& name,
			const float* verts, const float* texVerts, unsigned int vertSize,
			const unsigned int* indices, unsigned int indicesSize)
	{
		VertexArray* vertexArray = GetVertexArray(name);
		if (vertexArray != nullptr)
		{
			return vertexArray;
		}
		vertexArray = new VertexArray(verts, texVerts, vertSize, indices, indicesSize);
		mVertexArrays.emplace(name, vertexArray);
		return vertexArray;
	}

	VertexArray* TowerDefense::VertexArrayManager::CreateSpriteVertexArray(
		const std::string& name, const Vector2& spriteSize, const Vector2& minTexPos, const Vector2& maxTexPos)
	{
		VertexArray* vertexArray = GetVertexArray(name);
		if (vertexArray != nullptr)
		{
			// TODO: Implementation
		}
		// TODO: Implementation
		return nullptr;
	}

	VertexArray* TowerDefense::VertexArrayManager::GetVertexArray(const std::string& name) const
	{
		const auto& foundVertArray = mVertexArrays.find(name);
		if (foundVertArray != mVertexArrays.end())
		{
			return (*foundVertArray).second;
		}
		return nullptr;
	}

}
