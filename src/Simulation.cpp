#include "Simulation.hpp"
#include "raylib.h"
#include "GameData.hpp"
#include "Utils.hpp"
#include "Logger.hpp"
#include "raymath.h"
#include "Renderer.hpp"

namespace Simulation
{
    GameData::Basedata basedata = GameData::Basedata();
    GameData::Lakedetails lakedetails = GameData::Lakedetails();
    int yearsuntilavillageiscreatednearby = 0;

     void fastforward() 
    {
        if (GameData::currentscene != GameData::Scene::playing) 
            return;

        // just clear, no need for size()-1
        GameData::textureint.clear();
        GameData::nearbypopulation = 0;

        // iterate safely over all bases
        for (std::size_t i = 0; i < GameData::bases.size(); i++)
        {
            GameData::Basedata& baseData = GameData::bases[i]; // reference so we modify in-place

            baseData.population += GetRandomValue(
                1,
                Utils::Clamp(2 * (int)baseData.basetype * baseData.population / 3, 1, 10)
            );

            GameData::nearbypopulation += baseData.population;

            if (!lakedetails.issecuredbyunesco) {
                if (lakedetails.usedforhygine)
                    lakedetails.damagelvl += baseData.population / 4.0f / 100.0f;
                if (lakedetails.usedformanifactioring)
                    lakedetails.damagelvl += baseData.population / 1.5f / 100.0f;

                lakedetails.damagelvl += baseData.population / 3.0f / 100.0f;
            } else {
                lakedetails.damagelvl += baseData.population / 6.0f / 100.0f;
            }

            if (lakedetails.damagelvl >= 100.0f) {
                GameData::currentscene = GameData::Scene::end;
                return;
            }

            baseData.exploredradious += baseData.population * (int)baseData.basetype;

            if (baseData.population < 50) {
                baseData.basetype = GameData::Basetype::village;
            }
            else if (baseData.population > 1500) {
                if (baseData.basetype != GameData::Basetype::city)
                    Logger::sendmessage("vesnice byla vylepsena na mesto"); 
                baseData.basetype = GameData::Basetype::city;
            }
            else if (baseData.population < 500000 && baseData.population > 10000) {
                if (baseData.basetype != GameData::Basetype::metrocity)
                    Logger::sendmessage("mesto bylo vylepseno na metropoli"); 
                baseData.basetype = GameData::Basetype::metrocity;
            }

            if (Renderer::RenderUtils::distancecalc(
                    baseData.cords,
                    { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f }) 
                <= baseData.exploredradious)
            {
                if (!baseData.discovered) {
                    baseData.discovered = true;
                    Logger::sendmessage("jezero bylo objeveno vesnici c." +
                        std::to_string(Utils::Clamp((int)i, 1, 9999)));
                    baseData.yearoflakediscovery = (int)GameData::year;
                }
            }
        }

        Logger::sendmessage("rok preskocen");
        GameData::year += 1.0f;

        if (yearsuntilavillageiscreatednearby <= 0) {
            basedata.basetype = GameData::Basetype::village;
            basedata.cords = { (float)GetRandomValue(-948, 948),
                               (float)GetRandomValue(-948, 948) };
            basedata.townname = GameData::townnames[
                GetRandomValue(0, (int)GameData::townnames.size() - 1)
            ];
            basedata.yearwhenwasfounded = (int)GameData::year;

            while (Renderer::RenderUtils::distancecalc(
                       basedata.cords,
                       { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f }) < 100.0f)
            {
                basedata.cords = { (float)GetRandomValue(-948, 948),
                                   (float)GetRandomValue(-948, 948) };
            }

            basedata.population = 1;
            yearsuntilavillageiscreatednearby = GetRandomValue(25, 75);
            Logger::sendmessage("vesnice byla zalozena na " +
                std::to_string(basedata.cords.x * -1) + " X " +
                std::to_string(basedata.cords.y * -1) + " Y ");
            GameData::bases.push_back(basedata);
        }
        else {
            yearsuntilavillageiscreatednearby -= 1;
        }

        int totalofdaysthatitrained = GetRandomValue(0, 200);

        lakedetails.damagelvl = Utils::Clamp(
            lakedetails.damagelvl - (lakedetails.damagelvl / 100.0f * totalofdaysthatitrained),
            0.0f,
            100.0f
        );

        GameData::GameConfig::renderrainparticles = (totalofdaysthatitrained >= 150);

        GameData::peoplepositions.clear();

        for (int y = -1024; y < 1024; y++)
        {
            for (int x = -1024; x < 1024; x++)
            {
                if (GetRandomValue(1, 2048) == 1024)
                {
                    if ((int)GameData::peoplepositions.size() < GameData::nearbypopulation)
                    {
                        Vector2 pos = { (float)x, (float)y };

                        bool exists = false;
                        for (std::size_t i = 0; i < GameData::textureint.size(); ++i)
                        {
                            if (GameData::textureint[i].first.x == pos.x &&
                                GameData::textureint[i].first.y == pos.y)
                            {
                                exists = true;
                                break;
                            }
                        }

                        if (!exists)
                        {
                            int randomTex = GetRandomValue(
                                0,
                                (int)Renderer::Textures::people.size() - 1
                            );
                            GameData::textureint.push_back(std::make_pair(pos, randomTex));
                        }

                        for (std::size_t i = 0; i < GameData::bases.size(); ++i)
                        {
                            if (Vector2Distance(GameData::bases[i].cords, pos) < 100.0f)
                            {
                                GameData::peoplepositions.push_back(pos);
                                break;
                            }
                        }
                    }
                }
            }
        }

        Renderer::RenderUtils::confirmposition();
    }
}