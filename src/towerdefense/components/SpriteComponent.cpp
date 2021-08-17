#include "SpriteComponent.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "GameRenderer.h"
#include "ShaderManager.h"
#include "GLBuffers.h"
#include "Texture.h"
#include "TexturesManager.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <utility>


namespace TowerDefense
{

	// ------------------- The Sprite Component Definition -------------------


	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
	    mDrawLayer = 0;
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mSize = Vector2::Zero();
		mRotationOffset = 0.0f;
		mTexCoords = TextureCoords();
		mSizeChanged = GenericEventCallback<const Vector2&>();
		mColorMultiplier = Color::GetWhite();
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::SpriteComponent(const std::string& textureFile, Actor* actor)
		: Component(actor)
	{
        mDrawLayer = 0;
        mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mSize = Vector2::Zero();
		mTexCoords = TextureCoords();
		mRotationOffset = 0.0f;
		mSizeChanged = GenericEventCallback<const Vector2&>();
        mColorMultiplier = Color::GetWhite();
        SetTexture(textureFile);
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
	}

	void SpriteComponent::SetDrawLayer(unsigned int drawLayer)
	{
	    if(mDrawLayer != drawLayer)
        {
            mDrawLayer = drawLayer;
            mRenderer->ReOrderSpriteComponents();
        }
	}

	unsigned int SpriteComponent::GetDrawLayer() const
	{
	    return mDrawLayer;
	}

	void SpriteComponent::SetSize(float x, float y)
    {
	    Vector2 size = Vector2(x, y);
	    SetSize(size);
    }

	void SpriteComponent::SetSize(const Vector2& size)
    {
        if (size != mSize)
        {
            mSizeChanged.Invoke(size);
        }
        mSize = size;
    }

	const Vector2& SpriteComponent::GetSize() const
	{
		return mSize;
	}

	void SpriteComponent::SetRotationOffset(float rotationOffset, bool inRadians)
	{
		mRotationOffset = inRadians ? rotationOffset : 
			(float)(M_PI / 180.0f) * rotationOffset;
	}

	float SpriteComponent::GetRotationOffset() const
	{
		return mRotationOffset;
	}

	void SpriteComponent::SetSizeChangedCallback(std::function<void(const Vector2&)> func)
	{
		mSizeChanged.SetCallback(std::move(func));
	}

	void SpriteComponent::SetColorMultiplier(const Color &colorMultiplier)
    {
	    mColorMultiplier = colorMultiplier;
    }

    const Color& SpriteComponent::GetColorMultiplier() const
    {
	    return mColorMultiplier;
    }

	void SpriteComponent::SetTexCoords(const Vector2& center, const Vector2& size)
	{
		SetSize(size);
		mTexCoords = TextureCoords::CreateTexCoords(center, size, mTexture);
	}

	const TextureCoords& SpriteComponent::GetTexCoords() const
	{
		return mTexCoords;
	}

	void SpriteComponent::SetTexture(Texture* texture)
	{
		if (texture == nullptr)
		{
			return;
		}
		mTexture = texture;
        SetSize(static_cast<float>(texture->GetWidth()),
                static_cast<float>(texture->GetHeight()));
		mTexCoords = TextureCoords();
	}

	void SpriteComponent::SetTexture(const std::string& file)
	{
		SetTexture(mTexturesManager->GetTexture(file));
	}

	Texture* SpriteComponent::GetTexture() const
	{
		return mTexture;
	}

	void SpriteComponent::SetShader(Shader* shader)
	{
		mShader = shader;
	}

	Shader* SpriteComponent::GetShader() const
	{
		return mShader;
	}

	void SpriteComponent::Draw()
	{
		if (!IsEnabled()
			|| !mOwner->IsActive())
		{
			return;
		}

		if (mTexture == nullptr)
		{
			return;
		}

		Matrix4 scaleMatrix = Matrix4::CreateScale(mSize.x, mSize.y, 1.0f);
		Matrix4 rotationMatrix = Matrix4::CreateRotation2D(mRotationOffset);
		Matrix4 worldTransform = scaleMatrix * rotationMatrix
			* mTransform->CreateTransformMatrix();

		mTexCoords.SetTexCoords(mRenderer->GetDefaultUVBuffer());
		mShader->Bind();
		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		mShader->SetMatrix4Uniform("uViewProjection", mRenderer->GetViewProjectionMatrix());
		mShader->SetVec4Uniform("uColorMultiplier", mColorMultiplier);

		mTexture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}