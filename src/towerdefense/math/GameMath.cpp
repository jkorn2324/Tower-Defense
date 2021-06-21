#include "GameMath.h"

namespace TowerDefense
{

    float Deg2Rad(float angle)
    {
        return PI / 180.0f * angle;
    }

    float Rad2Deg(float angle)
    {
        return 180.0f / PI * angle;
    }

    float Sin(float angleTheta)
    {
        return static_cast<float>(std::sin(angleTheta));
    }

    float Cos(float angleTheta)
    {
        return static_cast<float>(std::cos(angleTheta));
    }

    float Tan(float angleTheta)
    {
        return static_cast<float>(std::tan(angleTheta));
    }

    float ACos(float f)
    {
        return static_cast<float>(std::acosf(f));
    }

    float ATan2(float y, float x)
    {
        return static_cast<float>(std::atan2(y, x));
    }

    float Abs(float value)
    {
        return static_cast<float>(std::abs(value));
    }

    float Sqrt(float value)
    {
        return static_cast<float>(std::sqrt(value));
    }
}