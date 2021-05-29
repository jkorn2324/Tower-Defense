#pragma once

#include "Component.h"

#include <string>

namespace TowerDefense
{

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(class Actor* owner);
		SpriteComponent(const std::string& textureFile, class Actor* owner);
		virtual ~SpriteComponent();

	public:
		void SetTexture(class Texture* texture);
		void SetTexture(const std::string& file);
		class Texture* GetTexture() const;
		void SetShader(class Shader* shader);
		class Shader* GetShader() const;

		// TODO: Vertex Array Integration

	public:
		void SetRotationOffset(float rotation, bool inRadians = false);
		float GetRotationOffset() const;

	public:
		void Draw();

	protected:
		class TexturesManager* mTexturesManager;
		class VertexArrayManager* mVertexArrayManager;
		class GameRenderer* mRenderer;
		class Texture* mTexture;

	private:
		class VertexArray* mVertexArray;
		class Shader* mShader;
		float mRotationOffset;
	};
}