#pragma once

#include <string>

namespace TowerDefense
{

	class Texture
	{
	public:
		Texture();
		~Texture();

	public:
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
	};
}