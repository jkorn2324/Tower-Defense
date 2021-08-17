#pragma once

#include "Component.h"
#include "Vector2.h"
#include "EventCallback.h"
#include "Color.h"
#include "Texture.h"

#include <string>
#include <functional>

namespace TowerDefense
{

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(class Actor* owner);
		SpriteComponent(const std::string& textureFile, class Actor* owner);
		virtual ~SpriteComponent();

	public:
		virtual void SetTexture(class Texture* texture);
		virtual void SetTexture(const std::string& file);
		class Texture* GetTexture() const;
		void SetShader(class Shader* shader);
		class Shader* GetShader() const;

	public:
	    void SetColorMultiplier(const Color& colorMultiplier);
	    const Color& GetColorMultiplier() const;

	public:
		void SetSizeChangedCallback(std::function<void(const Vector2&)> func);
		const Vector2& GetSize() const;

	private:
	    void SetSize(float x, float y);
	    void SetSize(const Vector2& size);

	public:
		void SetRotationOffset(float rotation, bool inRadians = false);
		float GetRotationOffset() const;

		void SetTexCoords(const Vector2& centerPos, const Vector2& size);
		const TextureCoords& GetTexCoords() const;
		unsigned int GetDrawLayer() const;
		void SetDrawLayer(unsigned int drawLayer);

	public:
		void Draw();

	protected:
		class TexturesManager* mTexturesManager;
		class GameRenderer* mRenderer;
		TextureCoords mTexCoords;

	private:
	    unsigned int mDrawLayer;
	    GenericEventCallback<const Vector2&> mSizeChanged;
		class Texture* mTexture;
		class Shader* mShader;
		Vector2 mSize;
		float mRotationOffset;
		Color mColorMultiplier;

	public:
	    friend class Tower;
	};
}