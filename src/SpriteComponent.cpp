#include "SpriteComponent.h"
#include "Matrix4.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "GameRenderer.h"
#include "ShaderManager.h"
#include "TexturesManager.h"
#include "Texture.h"

namespace TowerDefense
{

	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
		mTexture = nullptr;
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
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
		Matrix4 worldTransform = scaleMatrix * mOwner->GetTransform().GetTransformMatrix();

		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}