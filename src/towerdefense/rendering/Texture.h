#pragma once

#include <string>

#include "Vector2.h"

namespace TowerDefense
{

#pragma region texture_coords

    /**
      * Sets the sprite texture coords.
      */
    struct TextureCoords
    {
    public:
        TextureCoords();

    public:
        Vector2 GetCenterPoint() const;
        void SetTexCoords(class VertexBuffer* vertexArray);

    public:
        static TextureCoords CreateTexCoords(const Vector2& centerPoint,
                                             const Vector2& size, class Texture* texture);

    public:
        Vector2 min;
        Vector2 max;
    };

#pragma endregion

#pragma region texture

	class Texture
	{
	public:
		Texture();
		~Texture();

	public:
		bool IsLoaded() const;
		const std::string& GetFileName() const;
		bool Load(const std::string& file);
		void UnLoad();
		void Bind();

	public:
		unsigned int GetWidth();
		unsigned int GetHeight();

	private:
		unsigned int mTextureID;
		unsigned int mWidth;
		unsigned int mHeight;

	private:
		bool mLoaded;
		std::string mFileName;
	};

#pragma endregion
}