#pragma once

#include "Component.h"
#include "Vector2.h"

#include <string>

namespace TowerDefense
{

	/**
	 * Sets the sprite texture coords. 
	 */
	struct SpriteTexCoords
	{
	public:
		SpriteTexCoords();

	public:
		Vector2 GetCenterPoint() const;
		void SetTexCoords(class VertexArray* vertexArray);

	public:
		static SpriteTexCoords CreateTexCoords(const Vector2& centerPoint, 
			const Vector2& size, class Texture* texture);

	public:
		Vector2 min;
		Vector2 max;
	};

	/**
	 * The sprite component. 
	 */
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

	public:
		const SpriteTexCoords& GetTexCoords() const;
		void SetTexCoords(const SpriteTexCoords& texCoords);
		void SetTexCoords(const Vector2& min, const Vector2& max);

	public:
		void SetRotationOffset(float rotation, bool inRadians = false);
		float GetRotationOffset() const;

	public:
		void Draw();

	protected:
		class TexturesManager* mTexturesManager;
		class GameRenderer* mRenderer;
		class Texture* mTexture;

	protected:
		SpriteTexCoords mTexCoords;

	private:
		class Shader* mShader;
		float mRotationOffset;
	};
}