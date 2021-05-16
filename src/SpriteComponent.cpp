#include "SpriteComponent.h"
#include "Matrix4.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "GameRenderer.h"
#include "ShaderManager.h"
#include "TexturesManager.h"
#include "Texture.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>


namespace TowerDefense
{

	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
		mTexture = nullptr;
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mRotationOffset = 0.0f;
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
	}

	void SpriteComponent::SetRotationOffset(float rotationOffset, bool inRadians)
	{
		mRotationOffset = inRadians ? rotationOffset : M_PI / 180.0f * rotationOffset;
	}

	float SpriteComponent::GetRotationOffset() const
	{
		return mRotationOffset;
	}

	void SpriteComponent::SetTexture(Texture* texture)
	{
		mTexture = texture;
	}

	void SpriteComponent::SetTexture(const std::string& file)
	{
		mTexture = mTexturesManager->GetTexture(file);
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

		mShader->Bind();
		mTexture->Bind();

		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTexture->GetWidth()),
			static_cast<float>(mTexture->GetHeight()), 1.0f);
		Matrix4 rotationMatrix = Matrix4::CreateRotation2D(mRotationOffset);
		Matrix4 spriteTransformMatrix = scaleMatrix * rotationMatrix;
		Matrix4 worldTransform = spriteTransformMatrix * mOwner->GetTransform().GetTransformMatrix();

		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}