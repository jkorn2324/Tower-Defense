#pragma once

namespace TowerDefense
{

    class Color
    {
    public:
        Color();
        Color(float r, float g, float b, float a);

    public:
        const float* FloatPointer() const;

    public:
        friend bool operator==(const Color& a, const Color& b);
        friend Color operator*(const Color& a, const Color& b);
        friend Color operator+(const Color& a, const Color& b);
        friend Color operator-(const Color& a, const Color& b);

    public:
        Color& operator*=(const Color& c);
        Color& operator+=(const Color& c);
        Color& operator-=(const Color& c);

    public:
        static Color GetRed();
        static Color GetGreen();
        static Color GetBlue();
        static Color GetWhite();
        static Color GetBlack();

    public:
        float r;
        float g;
        float b;
        float a;
    };
}