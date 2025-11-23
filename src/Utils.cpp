#include "Utils.hpp"
#include <vector>
#include "raylib.h"

namespace Utils
{
    void RemoveVector2(std::vector<Vector2>& vec, const std::vector<Vector2>& toRemove)
    {
        for (size_t i = 0; i < toRemove.size(); ++i)
        {
            Vector2 rm = toRemove[i];

            for (size_t j = 0; j < vec.size(); )
            {
                if (vec[j].x == rm.x && vec[j].y == rm.y)
                    vec.erase(vec.begin() + j);
                else
                    j++;
            }
        }
        return;
    }

    float Clamp(float value, float min, float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}