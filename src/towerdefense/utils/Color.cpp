#include "Color.h"

namespace TowerDefense
{

    Color::Color()
    {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        a = 1.0f;
    }

    Color::Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->b = b;
        this->g = g;
        this->a = a;
    }

    const float *Color::FloatPointer() const
    {
        return reinterpret_cast<const float*>(&(this->r));
    }

    bool operator==(const Color& a, const Color& b)
    {
        return a.r == b.r && a.g == b.g
            && a.b == b.b && a.a == b.a;
    }

    Color operator*(const Color& a, const Color& b)
    {
        return Color(a.r * b.r, a.g * b.g,
                     a.b * b.b, a.a * b.a);
    }

    Color operator+(const Color& a, const Color& b)
    {
        return Color(a.r + b.r, a.g + b.g,
                     a.b + b.b, a.g + b.g);
    }

    Color operator-(const Color& a, const Color& b)
    {
        return Color(a.r - b.r, a.g - b.g,
                     a.b - b.b, a.g - b.g);
    }

    Color& Color::operator*=(const Color &c)
    {
        this->r *= c.r;
        this->g *= c.g;
        this->b *= c.b;
        this->a *= c.a;
        return *this;
    }

    Color& Color::operator+=(const Color &c)
    {
        this->r += c.r;
        this->g += c.g;
        this->b += c.b;
        this->a += c.a;
        return *this;
    }

    Color& Color::operator-=(const Color &c)
    {
        this->r -= c.r;
        this->g -= c.g;
        this->b -= c.b;
        this->a -= c.a;
        return *this;
    }

    Color Color::GetBlack()
    {
        return Color(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Color Color::GetBlue()
    {
        return Color(0.0f, 0.0f, 1.0f, 1.0f);
    }

    Color Color::GetGreen()
    {
        return Color(0.0f, 1.0f, 0.0f, 1.0f);
    }

    Color Color::GetWhite()
    {
        return Color(1.0f, 1.0f, 1.0f, 1.0f);
    }

    Color Color::GetRed()
    {
        return Color(1.0f, 0.0f, 0.0f, 1.0f);
    }
}
