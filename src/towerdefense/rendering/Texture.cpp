#include "Texture.h"
#include "GameParameters.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

namespace TowerDefense
{

	Texture::Texture()
	{
		mFileName = "";
		mLoaded = false;
		mTextureID = 0;
		mWidth = 0;
		mHeight = 0;
	}

	Texture::~Texture() 
	{
		UnLoad();
	}

	bool Texture::IsLoaded() const
	{
		return mLoaded;
	}

	const std::string& Texture::GetFileName() const { return mFileName; }

	bool Texture::Load(const std::string& file)
	{
		if (mLoaded)
		{
			return true;
		}

		int numChannels = 0;
		int localWidth, localHeight;
		unsigned char* image = SOIL_load_image(file.c_str(), 
			&localWidth, &localHeight, &numChannels, SOIL_LOAD_AUTO);
		if (image == nullptr)
		{
		    if(DISPLAY_LOGS)
            {
                SDL_Log("Failed to load image %s: %s", file.c_str(), SOIL_last_result());
            }
			return false;
		}

		if(DISPLAY_LOGS)
        {
            SDL_Log("Successfully loaded image %s", file.c_str());
        }

		int format = numChannels == 4 ? GL_RGBA : GL_RGB;
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, localWidth, localHeight, 
			0, format, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		mWidth = static_cast<unsigned int>(localWidth);
		mHeight = static_cast<unsigned int>(localHeight);
		mLoaded = true;
		return true;
	}

	void Texture::UnLoad()
	{
		if (!mLoaded)
		{
			return;
		}
		mLoaded = false;
		glDeleteTextures(1, &mTextureID);
	}

	void Texture::Bind()
	{
		if (!mLoaded) 
		{
			return;
		}
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	unsigned int Texture::GetHeight() { return mHeight; }

	unsigned int Texture::GetWidth() { return mWidth; }
}