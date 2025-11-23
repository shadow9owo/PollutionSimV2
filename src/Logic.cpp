#include "Logic.hpp"
#include "raylib.h"
#include "GameData.hpp"

namespace Logic
{
    Vector2 GetLakeCords()
    {
        return {GameData::GameConfig::windowsize.x / 2.0f - 50, GameData::GameConfig::windowsize.y / 2.0f - 50};
    }
}