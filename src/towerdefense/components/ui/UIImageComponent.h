//
// Created by jkorn on 8/15/2021.
//

#pragma once

#include "Component.h"
#include "Color.h"
#include "Vector2.h"
#include "Texture.h"

#include <string>

namespace TowerDefense
{

    class UIImageComponent : public Component
    {
    public:
        UIImageComponent(class GameUIActor* owner);
        UIImageComponent(class GameUIActor* owner, unsigned int imageLayer);
        ~UIImageComponent();

    public:
        virtual void SetTexture(class Texture* texture);
        virtual void SetTexture(const std::string& file);
        class Texture* GetTexture() const;

    public:
        unsigned int GetDrawLayer() const;
        void SetDrawLayer(unsigned int drawLayer);

    public:
        void SetColorMultiplier(const Color& colorMultiplier);
        const Color& GetColorMultiplier() const;

    public:
        void SetTexCoords(const Vector2& center, const Vector2& size);
        const TextureCoords& GetTexCoords() const;

    public:
        const Vector2& GetSize() const;

    private:
        void SetSize(float x, float y);
        void SetSize(const Vector2& size);

    public:
        void Draw();

    private:
        Vector2 mSize;
        class Texture* mTexture;
        class GameRenderer* mRenderer;
        class Shader* mShader;
        unsigned int mDrawLayer;
        Color mColorMultiplier;
        TextureCoords mTexCoords;
    };
}
