#pragma once

#include <vector>
#include <string>

namespace TowerDefense
{

	class SpriteAnimation
	{

	public:
		SpriteAnimation(const std::string& name);
		~SpriteAnimation();

	public:
		void ResetTime();

	public:
		const std::string& GetName() const;
		void SetName(const std::string& name);
		void SetFramesPerSecond(float framesPerSecond);
		float GetFramesPerSecond() const;
		float GetDuration() const;

	public:
		void AddTexture(class Texture* texture);
		class Texture* GetTexture() const;

	public:
		void Update(float deltaTime);

	private:
		float GetTimePerFrame() const;

	private:
		std::vector<class Texture*> mTextures;
		std::string mAnimationName;

		float mCurrentTime, mFramesPerSecond;
		unsigned int mFrameIndex;
	};
}