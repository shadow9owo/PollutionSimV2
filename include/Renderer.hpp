#include <array>
#include "raylib.h"

namespace Renderer
{
    namespace RenderUtils
    {
        extern std::array<Texture2D,4> LoadPeople();

        extern void importpositions();

        extern void rendermap();

        extern void renderui();

        extern void DrawOutlinedText(const char* text, int x, int y, int fontSize, Color color, int outlineSize, Color outlineColor);

        extern float distancecalc(Vector2 a,Vector2 b);

        extern void confirmposition();
    }

    namespace Textures
    {
        extern Texture2D house;
        extern Texture2D city;
        extern Texture2D metrocity;
        extern Texture2D tree;
        extern Texture2D grass;
        extern Texture2D rock;
        extern std::array<Texture2D,4> people; 
        extern Texture2D background;
    }
    namespace Sounds
    {
        extern Sound rain;
        extern Sound bird;
    }

    extern void InitRenderer();
}