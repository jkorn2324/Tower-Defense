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
	SpriteTexCoords::SpriteTexCoords()
	{
		min = Vector2(0.0f, 0.0f);
		max = Vector2(1.0f, 1.0f);
	}
	
	Vector2 SpriteTexCoords::GetCenterPoint() const
	{
		return Vector2(
			(min.x + max.x) / 2.0f, 
			(min.y + max.y) / 2.0f);
	}

	void SpriteTexCoords::SetTexCoords(VertexArray* texCoords)
	{
		float texVertices[] =
		{
			min.x, min.y,
			max.x, min.y,
			max.x, max.y,
			min.x, max.y
		};
		texCoords->SetTexVerts(texVertices);
	}

	SpriteTexCoords SpriteTexCoords::CreateTexCoords(const Vector2& centerPoint, const Vector2& size, Texture* texture)
	{
		float halfSizeX = size.x * 0.5f;
		float halfSizeY = size.y * 0.5f;
		SpriteTexCoords coords;
		coords.min.x = (centerPoint.x - halfSizeX) / texture->GetWidth();
		coords.min.y = (centerPoint.y - halfSizeY) / texture->GetHeight();
		coords.max.x = (centerPoint.x + halfSizeX) / texture->GetWidth();
		coords.max.y = (centerPoint.x + halfSizeY) / texture->GetHeight();
		return coords;
	}

	// ------------------- The Sprite Component Definition -------------------

	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mVertexArray = nullptr;
		mTexCoords = SpriteTexCoords();
		mTexture = nullptr;
		mRotationOffset = 0.0f;
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::SpriteComponent(const std::string& textureFile, Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mVertexArray = nullptr;
		mTexCoords = SpriteTexCoords();
		mTexture = nullptr;
		mRotationOffset = 0.0f;
		SetTexture(textureFile);
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
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

	void SpriteComponent::SetTexCoords(const SpriteTexCoords& coords)
	{
		mTexCoords = coords;
	}

	void SpriteComponent::SetTexCoords(const Vector2& min, const Vector2& max)
	{
		mTexCoords.min = min;
		mTexCoords.max = max;
	}

	const SpriteTexCoords& SpriteComponent::GetTexCoords() const
	{
		return mTexCoords;
	}

	VertexArray* SpriteComponent::GetVertexArray() const
	{
		if (mVertexArray != nullptr)
		{
			return mVertexArray;
		}
		return mRenderer->GetDefaultVertexArray();
	}

	void SpriteComponent::SetTexture(Texture* texture)
	{
		if (texture == nullptr)
		{
			return;
		}
		SetTexCoords(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
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

		VertexArray* vertexArray = GetVertexArray();
		mTexCoords.SetTexCoords(vertexArray);
		
		vertexArray->Bind();
		mShader->Bind();

		const Vector2& scale = mTransform->GetScale();
		const Vector2& position = mTransform->GetPosition();
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTexture->GetWidth()) * scale.x,
			static_cast<float>(mTexture->GetHeight()) * scale.y, 1.0f);
		Matrix4 rotationMatrix = Matrix4::CreateRotation2D(
			mTransform->GetRotation() + mRotationOffset);
		Matrix4 positionMatrix = Matrix4::CreatePosition(
			position.x, position.y, 0.0f);
		Matrix4 worldTransform = scaleMatrix * rotationMatrix * positionMatrix;

		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		mShader->SetMatrix4Uniform("uViewProjection", mRenderer->GetViewProjectionMatrix());
		
		mTexture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}