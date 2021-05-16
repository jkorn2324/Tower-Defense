#include "AnimatedSpriteComponent.h"
#include "Actor.h"
#include "SpriteAnimation.h"

namespace TowerDefense
{

	AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner)
		: SpriteComponent(owner)
	{
		mCurrentAnimation = nullptr;
		mAnimations = std::vector<SpriteAnimation*>();
	}

	AnimatedSpriteComponent::~AnimatedSpriteComponent()
	{
		for (SpriteAnimation* animation : mAnimations)
		{
			delete animation;
		}
		mAnimations.clear();
	}

	void AnimatedSpriteComponent::PlayAnimation(const std::string& name)
	{
		const auto& searched = std::find_if(mAnimations.begin(), mAnimations.end(),
			[name](SpriteAnimation* animation) -> bool
			{
				return animation->GetName() == name;
			});
		if (searched != mAnimations.end())
		{
			mCurrentAnimation = *searched;
		}
	}

	void AnimatedSpriteComponent::AddAnimation(SpriteAnimation* animation)
	{
		if (animation == nullptr)
		{
			return;
		}

		const auto& searched = std::find_if(mAnimations.begin(), mAnimations.end(),
			[animation](SpriteAnimation* anim) -> bool
			{
				return anim->GetName() == animation->GetName();
			});
		if (searched != mAnimations.end())
		{
			return;
		}
		mAnimations.push_back(animation);
	}

	SpriteAnimation* AnimatedSpriteComponent::GetAnimation() const
	{
		return mCurrentAnimation;
	}

	void AnimatedSpriteComponent::Update(float deltaTime)
	{
		if (mCurrentAnimation != nullptr)
		{
			mCurrentAnimation->Update(deltaTime);
			SetTexture(mCurrentAnimation->GetTexture());
		}
	}
}