#pragma once

#include "Component.h"
#include "Vector2.h"
#include "EventCallback.h"
#include "Color.h"

#include <string>
#include <functional>

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
		void SetTexCoords(class VertexBuffer* vertexArray);

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
		const SpriteTexCoords& GetTexCoords() const;
		unsigned int GetDrawLayer() const;
		void SetDrawLayer(unsigned int drawLayer);

	public:
		void Draw();

	protected:
		class TexturesManager* mTexturesManager;
		class GameRenderer* mRenderer;
		SpriteTexCoords mTexCoords;

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