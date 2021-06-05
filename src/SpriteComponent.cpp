#include "SpriteComponent.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "GameRenderer.h"
#include "ShaderManager.h"
#include "VertexArray.h"
#include "Texture.h"
#include "TexturesManager.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>


namespace TowerDefense
{

	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mWidth = 0.0f;
		mHeight = 0.0f;
		mRotationOffset = 0.0f;
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::SpriteComponent(const std::string& textureFile, Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mWidth = 0.0f;
		mHeight = 0.0f;
		mRotationOffset = 0.0f;
		SetTexture(textureFile);
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
	}

	float SpriteComponent::GetHeight() const
	{
		return mHeight;
	}

	float SpriteComponent::GetWidth() const
	{
		return mWidth;
	}

	void SpriteComponent::SetRotationOffset(float rotationOffset, bool inRadians)
	{
		mRotationOffset = inRadians ? rotationOffset : 
			(M_PI / 180.0f) * rotationOffset;
	}

	float SpriteComponent::GetRotationOffset() const
	{
		return mRotationOffset;
	}

	void SpriteComponent::SetTexture(Texture* texture)
	{
		if (texture == nullptr)
		{
			return;
		}
		mTexture = texture;

		mWidth = static_cast<float>(texture->GetWidth());
		mHeight = static_cast<float>(texture->GetHeight());
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
		if (!IsEnabled())
		{
			return;
		}

		if (mTexture == nullptr)
		{
			return;
		}

		Matrix4 scaleMatrix = Matrix4::CreateScale(mWidth, mHeight, 1.0f);
		Matrix4 rotationMatrix = Matrix4::CreateRotation2D(mRotationOffset);
		Matrix4 worldTransform = scaleMatrix * rotationMatrix 
			* mTransform->CreateTransformMatrix();

		mShader->Bind();
		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		mShader->SetMatrix4Uniform("uViewProjection", mRenderer->GetViewProjectionMatrix());
		
		mTexture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}