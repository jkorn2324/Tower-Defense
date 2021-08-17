//
// Created by jkorn on 8/15/2021.
//

#include "UIImageComponent.h"

#include "GameUIActor.h"
#include "Game.h"
#include "TexturesManager.h"
#include "GameRenderer.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Matrix4.h"

namespace TowerDefense
{

    UIImageComponent::UIImageComponent(class GameUIActor *owner)
            : Component(reinterpret_cast<Actor*>(owner))
    {
        mDrawLayer = 0;
        mTexCoords = TextureCoords();
        mSize = Vector2::Zero();
        mRenderer = owner->GetGame()->GetRenderer();
        mShader = mRenderer->GetShaderManager()->GetDefaultShader();
        mTexture = nullptr;
        mColorMultiplier = Color::GetWhite();
        mRenderer->AddUIImageComponent(this);
    }

    UIImageComponent::UIImageComponent(class GameUIActor *owner, unsigned int drawLayer)
            : Component(reinterpret_cast<Actor*>(owner))
    {
        mDrawLayer = drawLayer;
        mTexCoords = TextureCoords();
        mSize = Vector2::Zero();
        mRenderer = owner->GetGame()->GetRenderer();
        mShader = mRenderer->GetShaderManager()->GetDefaultShader();
        mTexture = nullptr;
        mColorMultiplier = Color::GetWhite();
        mRenderer->AddUIImageComponent(this);
    }

    UIImageComponent::~UIImageComponent()
    {
        mRenderer->RemoveUIImageComponent(this);
    }

    unsigned int UIImageComponent::GetDrawLayer() const { return mDrawLayer;}

    void UIImageComponent::SetDrawLayer(unsigned int drawLayer)
    {
        mDrawLayer = drawLayer;
        mRenderer->ReOrderUIImageComponents();
    }

    void UIImageComponent::SetTexture(Texture *texture)
    {
        if(texture == nullptr)
        {
            return;
        }
        mTexture = texture;
        SetSize(static_cast<float>(texture->GetWidth()),
                static_cast<float>(texture->GetHeight()));
        mTexCoords = TextureCoords();
    }

    void UIImageComponent::SetTexture(const std::string &file)
    {
        TexturesManager* textureManager = (TexturesManager*)mOwner
                ->GetGame()->GetTexturesManager();
        if(textureManager != nullptr)
        {
            SetTexture(textureManager->GetTexture(file));
        }
    }

    class Texture* UIImageComponent::GetTexture() const { return mTexture; }

    void UIImageComponent::SetColorMultiplier(const Color &colorMultiplier)
    {
        mColorMultiplier = colorMultiplier;
    }

    const Color& UIImageComponent::GetColorMultiplier() const { return mColorMultiplier; }

    void UIImageComponent::SetTexCoords(const Vector2 &center, const Vector2 &size)
    {
        SetSize(size);
        mTexCoords = TextureCoords::CreateTexCoords(center, size, mTexture);
    }

    const TextureCoords& UIImageComponent::GetTexCoords() const { return mTexCoords; }

    const Vector2& UIImageComponent::GetSize() const { return mSize; }

    void UIImageComponent::SetSize(float x, float y)
    {
        Vector2 size(x, y);
        SetSize(size);
    }

    void UIImageComponent::SetSize(const Vector2 &size)
    {
        mSize = size;
    }

    void UIImageComponent::Draw()
    {
        if(!IsEnabled()
            || !mOwner->IsActive())
        {
            return;
        }
        Matrix4 scaleMatrix = Matrix4::CreateScale(mSize.x, mSize.y, 1.0f);
        Matrix4 worldTransform = scaleMatrix * mTransform->CreateTransformMatrix();

        mTexCoords.SetTexCoords(mRenderer->GetDefaultUVBuffer());
        mShader->Bind();
        mShader->SetMatrix4Uniform("uWorldTransform", worldTransform);
        mShader->SetMatrix4Uniform("uViewProjection", mRenderer->GetViewProjectionMatrix());
        mShader->SetVec4Uniform("uColorMultiplier", mColorMultiplier);

        mTexture->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
