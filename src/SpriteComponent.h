#pragma once

#include "Component.h"
#include <string>

namespace TowerDefense
{

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(class Actor* owner);
		virtual ~SpriteComponent();

	public:
		void SetTexture(class Texture* texture);
		void SetTexture(const std::string& file);
		class Texture* GetTexture() const;
		void SetShader(class Shader* shader);
		class Shader* GetShader() const;

	public:
		void Draw();

	private:
		class Shader* mShader;
		class TexturesManager* mTexturesManager;
		class GameRenderer* mRenderer;
		class Texture* mTexture;
	};
}