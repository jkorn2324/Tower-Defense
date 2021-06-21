#pragma once

#include <cmath>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

namespace TowerDefense
{
    const float PI = 3.14159265358979323;

    float Deg2Rad(float angle);
    float Rad2Deg(float angle);

    float Sin(float angleTheta);
    float Cos(float angleTheta);
    float Tan(float angleTheta);

    float ACos(float f);
    float ATan2(float y, float x);

    float Abs(float value);
    float Sqrt(float value);

    template<typename T>
    T Clamp(T value, T min, T max)
    {
        if(value < min)
        {
            return value;
        }

        if(value > max)
        {
            return max;
        }
        return value;
    }

    template<typename T>
    T Lerp(T min, T max, float alpha)
    {
        return min + (max - min) * alpha;
    }
}