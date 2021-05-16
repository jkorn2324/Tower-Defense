#include "SpriteAnimation.h"

#include "Texture.h"

namespace TowerDefense
{

	SpriteAnimation::SpriteAnimation(const std::string& name)
	{
		mTextures = std::vector<Texture*>();
		mFramesPerSecond = 20.0f;
		mAnimationName = name;
		mCurrentTime = 0.0f;
		mFrameIndex = 0;
	}

	SpriteAnimation::~SpriteAnimation()
	{
		mTextures.clear();
	}

	void SpriteAnimation::ResetTime()
	{
		mCurrentTime = 0.0f;
	}

	const std::string& SpriteAnimation::GetName() const
	{
		return mAnimationName;
	}

	void SpriteAnimation::SetName(const std::string& name)
	{
		mAnimationName = name;
	}

	void SpriteAnimation::SetFramesPerSecond(float framesPerSecond)
	{
		mFramesPerSecond = framesPerSecond;
	}

	float SpriteAnimation::GetFramesPerSecond() const
	{
		return mFramesPerSecond;
	}

	void SpriteAnimation::Update(float deltaTime)
	{
		mCurrentTime += deltaTime;
		
		float timePerFrame = GetTimePerFrame();
		float mCurrentFrameIndex = mCurrentTime / timePerFrame;
		
		if (mCurrentFrameIndex >= (float)mTextures.size())
		{
			mCurrentTime -= GetDuration();
			
			if (mCurrentTime <= 0.0f)
			{
				mCurrentTime = 0.0f;
			}
		}
		mFrameIndex = static_cast<unsigned int>(mCurrentTime / timePerFrame);
	}

	float SpriteAnimation::GetDuration() const
	{
		return GetTimePerFrame() * mTextures.size();
	}

	void SpriteAnimation::AddTexture(Texture* texture)
	{
		mTextures.push_back(texture);
	}

	float SpriteAnimation::GetTimePerFrame() const
	{
		return 1.0f / mFramesPerSecond;
	}

	Texture* SpriteAnimation::GetTexture() const
	{
		if (mTextures.size() <= 0 || mFrameIndex >= mTextures.size())
		{
			return nullptr;
		}
		return mTextures[mFrameIndex];
	}
}