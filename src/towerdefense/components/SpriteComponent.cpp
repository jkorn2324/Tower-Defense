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

	// ---------------------------- The Sprite Texture Coords Implementation -------------------------

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

	void SpriteTexCoords::SetTexCoords(VertexBuffer* buffer)
	{
		float texVertices[] =
		{
			min.x, min.y,
			max.x, min.y,
			max.x, max.y,
			min.x, max.y
		};
		buffer->SetVertices(texVertices, sizeof(texVertices), 4);
	}

	SpriteTexCoords SpriteTexCoords::CreateTexCoords(const Vector2& centerPoint, const Vector2& size, Texture* texture)
	{
		float halfSizeX = size.x * 0.5f;
		float halfSizeY = size.y * 0.5f;
		SpriteTexCoords coords;
		coords.min.x = (centerPoint.x - halfSizeX) / texture->GetWidth();
		coords.min.y = (centerPoint.y - halfSizeY) / texture->GetHeight();
		coords.max.x = (centerPoint.x + halfSizeX) / texture->GetWidth();
		coords.max.y = (centerPoint.y + halfSizeY) / texture->GetHeight();
		return coords;
	}

	// ------------------- The Sprite Component Definition -------------------


	SpriteComponent::SpriteComponent(Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mSize = Vector2::Zero();
		mRotationOffset = 0.0f;
		mTexCoords = SpriteTexCoords();
		mSizeChanged = EventCallback<const Vector2&>();
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::SpriteComponent(const std::string& textureFile, Actor* actor)
		: Component(actor)
	{
		mRenderer = actor->GetGame()->GetRenderer();
		mTexturesManager = actor->GetGame()->GetTexturesManager();
		mShader = mRenderer->GetShaderManager()->GetDefaultShader();
		mTexture = nullptr;
		mSize = Vector2::Zero();
		mTexCoords = SpriteTexCoords();
		mRotationOffset = 0.0f;
		mSizeChanged = EventCallback<const Vector2&>();
		SetTexture(textureFile);
		mRenderer->AddSpriteComponent(this);
	}

	SpriteComponent::~SpriteComponent() 
	{
		mRenderer->RemoveSpriteComponent(this);
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

	void SpriteComponent::SetTexCoords(const Vector2& center, const Vector2& size)
	{
		if (mSize != size)
		{
			mSizeChanged.Invoke(size);
		}
		mSize = size;
		mTexCoords = SpriteTexCoords::CreateTexCoords(center, size, mTexture);
	}

	const SpriteTexCoords& SpriteComponent::GetTexCoords() const
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

		Vector2 newSize;
		newSize.x = static_cast<float>(texture->GetWidth());
		newSize.y = static_cast<float>(texture->GetHeight());
		if (newSize != mSize)
		{
			mSizeChanged.Invoke(newSize);
		}
		mSize = newSize;
		mTexCoords = SpriteTexCoords();
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

		Matrix4 scaleMatrix = Matrix4::CreateScale(mSize.x, mSize.y, 1.0f);
		Matrix4 rotationMatrix = Matrix4::CreateRotation2D(mRotationOffset);
		Matrix4 worldTransform = scaleMatrix * rotationMatrix 
			* mTransform->CreateTransformMatrix();

		mTexCoords.SetTexCoords(mRenderer->GetDefaultUVBuffer());
		mShader->Bind();
		mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
		mShader->SetMatrix4Uniform("uViewProjection", mRenderer->GetViewProjectionMatrix());
		
		mTexture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}