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

    float ATan2(float y, float x);

    float Abs(float value);
    float Sqrt(float value);
}