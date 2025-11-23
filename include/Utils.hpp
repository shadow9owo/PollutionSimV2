#pragma once

#include <vector>
#include "raylib.h"

namespace Utils
{
    extern void RemoveVector2(std::vector<Vector2>& vec, const std::vector<Vector2>& toRemove);

    extern float Clamp(float value, float min, float max);
}