#pragma once

#include "SpriteComponent.h"

#include <vector>
#include <string>

namespace TowerDefense
{

	class AnimatedSpriteComponent : SpriteComponent
	{
	public:
		AnimatedSpriteComponent(class Actor* actor);
		~AnimatedSpriteComponent();

	public:
		void PlayAnimation(const std::string& animationName);
		void AddAnimation(class SpriteAnimation* animation);
		class SpriteAnimation* GetAnimation() const;

	public:
		virtual void Update(float deltaTime) override;

	private:
		class SpriteAnimation* mCurrentAnimation;
		std::vector<class SpriteAnimation*> mAnimations;
	};
}