#include "GameData.hpp"
#include "Logic.hpp"
#include <array>

namespace GameData
{
    const std::array<const char*, 37> townnames = {
        "Prague",
        "Brno",
        "Ostrava",
        "Plzen",
        "Liberec",
        "Olomouc",
        "Ceske Budejovice",
        "Hradec Kralove",
        "Pardubice",
        "Usti nad Labem",
        "Zlin",
        "Havirov",
        "Kladno",
        "Most",
        "Opava",
        "Frydek-Mistek",
        "Jihlava",
        "Teplice",
        "Karvina",
        "Karlovy Vary",
        "Chomutov",
        "Jablonec nad Nisou",
        "Mlada Boleslav",
        "Prostejov",
        "Prerov",
        "Ceska Lipa",
        "Trebic",
        "Tabor",
        "Znojmo",
        "Kolin",
        "Pribram",
        "Pisek",
        "Kromeriz",
        "Orlova",
        "Lisen",
        "Brevnov",
        "Vsetin"
    };

    std::vector<std::pair<Vector2,int>> textureint = std::vector<std::pair<Vector2,int>>();
    std::vector<Rectangle> notrenderable = std::vector<Rectangle>();
    bool dataloaded = false;
    std::vector<Vector2> peoplepositions = std::vector<Vector2>();
    std::vector<Vector2> grassposition = std::vector<Vector2>();
    std::vector<Vector2> treepositions = std::vector<Vector2>();
    std::vector<Vector2> rockpositions = std::vector<Vector2>();

    Vector2 position = {0,0};
    Scene currentscene = Scene::loading;
    Vector2 lakecords = Logic::GetLakeCords();
    std::vector<Basedata> bases = std::vector<Basedata>();
    std::vector<Particle> ParticleList = std::vector<Particle>();
    std::vector<std::pair<int,int>> positionoffsets = std::vector<std::pair<int,int>>();
    int nearbypopulation = 0;
    float year = 0.0f;

    namespace GameConfig 
    {
        bool renderrainparticles = false;
        bool debug = false;
        bool shouldexi = false;
        Vector2 windowsize = {800,480};
        float timescale = 1.0f;
    }
}