#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include <array>

namespace GameData
{
    enum Basetype
    {
        village = 1,
        city,
        metrocity
    };

    enum Scene
    {
        loading,
        menu,
        playing,
        paused,
        end
    };

    class Lakedetails
    {
        public:
            bool usedformanifactioring;
            bool usedforhygine;
            bool issecuredbyunesco;
            float damagelvl;
    };

    extern const std::array<const char*, 37>  townnames;

    extern std::vector<std::pair<Vector2,int>> textureint;
    extern std::vector<Rectangle> notrenderable;
    extern bool dataloaded;
    extern std::vector<Vector2> peoplepositions;
    extern std::vector<Vector2> grassposition;
    extern std::vector<Vector2> treepositions;
    extern std::vector<Vector2> rockpositions;
    
    class Basedata
    {
        public:
            bool discovered;
            int exploredradious;
            int population;
            Basetype basetype;
            Vector2 cords;
            int yearwhenwasfounded;
            int yearoflakediscovery;
            std::string townname;
    };
    struct Particle {
        Vector2 position;
        float velocity;
        Color color;
    
        Particle(Vector2 pos, float vel, Color col)
            : position(pos), velocity(vel), color(col) {}
    };

    extern Vector2 position;
    extern Scene currentscene;
    extern Vector2 lakecords;
    extern std::vector<Basedata> bases;
    extern std::vector<Particle> ParticleList;
    extern std::vector<std::pair<int,int>> positionoffsets;
    extern int nearbypopulation;
    extern float year;
    static constexpr int maxparticles = 2048;

    namespace GameConfig 
    {
        extern bool renderrainparticles;
        extern bool debug;
        extern bool shouldexi;
        extern Vector2 windowsize;
        extern float timescale;
    }
}