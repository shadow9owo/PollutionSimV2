#include "Renderer.hpp"
#include "raylib.h"
#include "IO.hpp"
#include <array>
#include "raymath.h"
#include <vector>
#include "GameData.hpp"
#include "Utils.hpp"
#include "Logger.hpp"
#include "Simulation.hpp"

namespace Renderer
{
    namespace RenderUtils
    {
        std::array<Texture2D,4> LoadPeople()
        {
            std::array<Texture2D,4> people;
            people[0] = LoadTexture((IO::GetCurrentDir() + "\\assets\\person1.png").c_str());
            people[1] = LoadTexture((IO::GetCurrentDir() + "\\assets\\person2.png").c_str());
            people[2] = LoadTexture((IO::GetCurrentDir() + "\\assets\\person3.png").c_str());
            people[3] = LoadTexture((IO::GetCurrentDir() + "\\assets\\person4.png").c_str());
            return people;
        }

        void importpositions() 
        {
            Logger::sendmessage("generuji pozice kamenu na mape");
        
            for (int y = -2048; y < 2048; y++)
            {
                for (int x = -2048; x < 2048; x++)
                {
                    if (GetRandomValue(1, 1023) == 512)
                    {
                        Vector2 pos = { (float)x, (float)y };
                    
                        if (GameData::bases.size() > 0)
                        {
                            for (size_t i = 0; i < GameData::bases.size(); i++)
                            {
                                auto& item = GameData::bases[i];
                            
                                if (distancecalc(item.cords, pos) >= 100 &&
                                    distancecalc(item.cords, GameData::lakecords + GameData::position) >= 100)
                                {
                                    GameData::rockpositions.push_back(pos);
                                }
                            }
                        }
                        else
                        {
                            GameData::rockpositions.push_back(pos);
                        }
                    }
                }
            }
        
            Logger::sendmessage("generuji pozice stromu na mape");
        
            for (int y = -2048; y < 2048; y++)
            {
                for (int x = -2048; x < 2048; x++)
                {
                    if (GetRandomValue(1, 1023) == 512)
                    {
                        Vector2 pos = { (float)x, (float)y };
                    
                        if (GameData::bases.size() > 0)
                        {
                            for (size_t i = 0; i < GameData::bases.size(); i++)
                            {
                                auto& item = GameData::bases[i];
                            
                                if (distancecalc(item.cords, pos) >= 100 &&
                                    distancecalc(item.cords, GameData::lakecords + GameData::position) >= 100)
                                {
                                    GameData::treepositions.push_back(pos);
                                }
                            }
                        }
                        else
                        {
                            GameData::treepositions.push_back(pos);
                        }
                    }
                }
            }
        
            Logger::sendmessage("generuji pozice travy na mape");
        
            for (int y = -2048; y < 2048; y++)
            {
                for (int x = -2048; x < 2048; x++)
                {
                    if (GetRandomValue(1, 1023) == 512)
                    {
                        Vector2 pos = { (float)x, (float)y };
                    
                        if (GameData::bases.size() > 0)
                        {
                            for (size_t i = 0; i < GameData::bases.size(); i++)
                            {
                                auto& item = GameData::bases[i];
                            
                                if (distancecalc(item.cords, pos) >= 100 &&
                                    distancecalc(item.cords, GameData::lakecords + GameData::position) >= 100)
                                {
                                    GameData::grassposition.push_back(pos);
                                }
                            }
                        }
                        else
                        {
                            GameData::grassposition.push_back(pos);
                        }
                    }
                }
            }
        
            Logger::sendmessage("potvrzuji pozice");
            Renderer::RenderUtils::confirmposition();
        
            Logger::sendmessage("nacteno");
            //WaitTime(2);
        
            GameData::dataloaded = true;
            GameData::currentscene = GameData::Scene::menu;
        
            return;
        }

        void rendermap()
        {
            for (size_t i = 0; i < GameData::bases.size(); i++)
            {
                GameData::Basedata& baseData = GameData::bases[i];
            
                Vector2 baseScreenPos = Vector2Add(baseData.cords, GameData::position);

                if (baseData.discovered)
                {
                    Vector2 center = {
                        GameData::GameConfig::windowsize.x / 2.0f + GameData::position.x,
                        GameData::GameConfig::windowsize.y / 2.0f + GameData::position.y
                    };
                
                    DrawLineEx(baseScreenPos, center, 12, {127,106,79,255});
                }

                switch (baseData.basetype)
                {
                    case GameData::village:
                    {
                        Rectangle src = {0,0,(float)Textures::house.width,(float)Textures::house.height};
                        Rectangle dest = {
                            baseScreenPos.x - Textures::house.width*2,
                            baseScreenPos.y - Textures::house.height*2,
                            Textures::house.width*4,
                            Textures::house.height*4
                        };
                        DrawTexturePro(Textures::house, src, dest, {0,0}, 0, WHITE);
                        break;
                    }
                
                    case GameData::city:
                    {
                        Rectangle src = {0,0,(float)Textures::city.width,(float)Textures::city.height};
                        Rectangle dest = {
                            baseScreenPos.x - Textures::city.width*2,
                            baseScreenPos.y - Textures::city.height*2,
                            Textures::city.width*4,
                            Textures::city.height*4
                        };
                        DrawTexturePro(Textures::city, src, dest, {0,0}, 0, WHITE);
                        break;
                    }
                
                    case GameData::metrocity:
                    {
                        Rectangle src = {0,0,(float)Textures::metrocity.width,(float)Textures::metrocity.height};
                        Rectangle dest = {
                            baseScreenPos.x - Textures::metrocity.width*2,
                            baseScreenPos.y - Textures::metrocity.height*2,
                            Textures::metrocity.width*4,
                            Textures::metrocity.height*4
                        };
                        DrawTexturePro(Textures::metrocity, src, dest, {0,0}, 0, WHITE);
                        break;
                    }
                
                    default: break;
                }

                if (!GameData::peoplepositions.empty())
                {
                    for (size_t j = 0; j < GameData::peoplepositions.size(); j++)
                    {
                        Vector2 pos = Vector2Add(GameData::peoplepositions[j], GameData::position);
                    
                        int texIndex = 0;
                        for (size_t k = 0; k < GameData::textureint.size(); k++)
                        {
                            if (GameData::textureint[k].first.x == GameData::peoplepositions[j].x &&
                                GameData::textureint[k].first.y == GameData::peoplepositions[j].y)
                            {
                                texIndex = GameData::textureint[k].second;
                                break;
                            }
                        }
                    
                        DrawTextureEx(Textures::people[texIndex], pos, 0, 2, WHITE);
                    }
                }

                std::string townText =
                    baseData.townname + " " + std::to_string(baseData.yearwhenwasfounded);
            
                Vector2 townDrawPos = Vector2Add(baseData.cords, GameData::position);
            
                DrawTextEx(GetFontDefault(), townText.c_str(), townDrawPos, 20, 0.5f, WHITE);
            }

            Vector2 lakeCenter = {
                GameData::GameConfig::windowsize.x / 2.0f + GameData::position.x,
                GameData::GameConfig::windowsize.y / 2.0f + GameData::position.y
            };
        
            DrawCircle((int)lakeCenter.x, (int)lakeCenter.y, 120, BROWN);
            DrawCircle((int)lakeCenter.x, (int)lakeCenter.y, 100,
                       {102,191,255, (unsigned char)(255 * (1 - (int)Simulation::lakedetails.damagelvl / 100))});

            for (size_t i = 0; i < GameData::rockpositions.size(); i++)
            {
                Vector2 screenPos = Vector2Add(GameData::rockpositions[i], GameData::position);

                if (screenPos.x + Textures::rock.width > 0 && screenPos.x < GameData::GameConfig::windowsize.x &&
                    screenPos.y + Textures::rock.height > 0 && screenPos.y < GameData::GameConfig::windowsize.y)
                {
                    DrawTextureEx(Textures::rock, screenPos, 0, 0.5f, WHITE);
                }
            }

            for (size_t i = 0; i < GameData::grassposition.size(); i++)
            {
                Vector2 screenPos = Vector2Add(GameData::grassposition[i], GameData::position);
            
                if (screenPos.x + Textures::grass.width > 0 && screenPos.x < GameData::GameConfig::windowsize.x &&
                    screenPos.y + Textures::grass.height > 0 && screenPos.y < GameData::GameConfig::windowsize.y)
                {
                    DrawTextureEx(Textures::grass, screenPos, 0, 0.5f, WHITE);
                }
            }

            for (size_t i = 0; i < GameData::treepositions.size(); i++)
            {
                Vector2 screenPos = Vector2Add(GameData::treepositions[i], GameData::position);
            
                if (screenPos.x + Textures::tree.width > 0 && screenPos.x < GameData::GameConfig::windowsize.x &&
                    screenPos.y + Textures::tree.height > 0 && screenPos.y < GameData::GameConfig::windowsize.y)
                {
                    DrawTextureEx(Textures::tree, screenPos, 0, 1.4f, WHITE);
                }
            }

            Vector2 textSize = MeasureTextEx(GetFontDefault(), "jezero", 20, 0.5f);
        
            DrawText("jezero",
                     (int)(lakeCenter.x - textSize.x/2),
                     (int)(lakeCenter.y - textSize.y/2),
                     20, WHITE);
        }

        void renderui()
        {
            DrawRectangleRec(
                {0, GameData::GameConfig::windowsize.y / 1.1f, 1000, 1000},
                GRAY
            );

            int pop = Utils::Clamp(GameData::nearbypopulation, 0, 10000);
        
            std::string popText = "populace: " + std::to_string(pop);
            DrawTextEx(GetFontDefault(), popText.c_str(),
                       {8, GameData::GameConfig::windowsize.y / 1.05f}, 18, 0.5f, BLACK);

            float pol = (int)(Simulation::lakedetails.damagelvl * 100) / 100.0f;
            std::string polText = "znecisteni (%) : " + std::to_string(pol) + " %";
        
            Vector2 polSize = MeasureTextEx(GetFontDefault(), polText.c_str(), 18, 1.05f);
        
            DrawTextEx(GetFontDefault(), polText.c_str(),
                       {polSize.x + 16, GameData::GameConfig::windowsize.y / 1.05f},
                       18, 0.5f, BLACK);

            int yearVal = Utils::Clamp((int)GameData::year, 0, 9999);
            std::string yearText = "rok: " + std::to_string(yearVal);
        
            DrawTextEx(GetFontDefault(), yearText.c_str(),
                       {polSize.x + 16 + polSize.x + 32, GameData::GameConfig::windowsize.y / 1.05f},
                       16, 0.05f, BLACK);
        }

        void DrawOutlinedText(const char* text, int x, int y, int fontSize, Color color, int outlineSize, Color outlineColor)
        {
            DrawText(text, x - outlineSize, y - outlineSize, fontSize, outlineColor);
            DrawText(text, x + outlineSize, y - outlineSize, fontSize, outlineColor);
            DrawText(text, x - outlineSize, y + outlineSize, fontSize, outlineColor);
            DrawText(text, x + outlineSize, y + outlineSize, fontSize, outlineColor);
            DrawText(text, x, y, fontSize, color);
        }

        void confirmposition()
        {
            for (size_t i = 0; i < GameData::bases.size(); ++i)
            {
                Vector2 basePos = GameData::bases[i].cords;

                std::vector<Vector2> rocksToRemove;
                for (size_t j = 0; j < GameData::rockpositions.size(); ++j)
                {
                    Vector2 p = GameData::rockpositions[j];
                    if (distancecalc(basePos, p) < 172 ||
                        distancecalc(basePos, GameData::lakecords + GameData::position) < 172)
                    {
                        rocksToRemove.push_back(p);
                    }
                }
                Utils::RemoveVector2(GameData::rockpositions, rocksToRemove);

                std::vector<Vector2> treesToRemove;
                for (size_t j = 0; j < GameData::treepositions.size(); ++j)
                {
                    Vector2 p = GameData::treepositions[j];
                    if (distancecalc(basePos, p) < 172 ||
                        distancecalc(basePos, GameData::lakecords + GameData::position) < 172)
                    {
                        treesToRemove.push_back(p);
                    }
                }
                Utils::RemoveVector2(GameData::treepositions, treesToRemove);

                std::vector<Vector2> grassToRemove;
                for (size_t j = 0; j < GameData::grassposition.size(); ++j)
                {
                    Vector2 p = GameData::grassposition[j];
                    if (distancecalc(basePos, p) < 172 ||
                        distancecalc(basePos, GameData::lakecords + GameData::position) < 172)
                    {
                        grassToRemove.push_back(p);
                    }
                }
                Utils::RemoveVector2(GameData::grassposition, grassToRemove);
            }
        
            Vector2 lake = GameData::lakecords;
        
            std::vector<Vector2> rocksLakeRemove;
            for (size_t j = 0; j < GameData::rockpositions.size(); ++j)
                if (distancecalc(lake, GameData::rockpositions[j]) < 172)
                    rocksLakeRemove.push_back(GameData::rockpositions[j]);
            Utils::RemoveVector2(GameData::rockpositions, rocksLakeRemove);
        
            std::vector<Vector2> treesLakeRemove;
            for (size_t j = 0; j < GameData::treepositions.size(); ++j)
                if (distancecalc(lake, GameData::treepositions[j]) < 172)
                    treesLakeRemove.push_back(GameData::treepositions[j]);
            Utils::RemoveVector2(GameData::treepositions, treesLakeRemove);
        
            std::vector<Vector2> grassLakeRemove;
            for (size_t j = 0; j < GameData::grassposition.size(); ++j)
                if (distancecalc(lake, GameData::grassposition[j]) < 172)
                    grassLakeRemove.push_back(GameData::grassposition[j]);
            Utils::RemoveVector2(GameData::grassposition, grassLakeRemove);
        }


        float distancecalc(Vector2 a,Vector2 b) {
            return Vector2Distance(a,b);
        }
    }

    namespace Textures
    {
        Texture2D house = {};
        Texture2D city = {};
        Texture2D metrocity = {};
        Texture2D tree = {};
        Texture2D grass = {};
        Texture2D rock = {};
        std::array<Texture2D,4> people; 
        Texture2D background = {};
    }
    namespace Sounds
    {
        Sound rain = {};
        Sound bird = {};
    }

    void InitRenderer()
    {
        Sounds::rain = LoadSound((IO::GetCurrentDir() + "\\assets\\rain.wav").c_str());
        Sounds::bird = LoadSound((IO::GetCurrentDir() + "\\assets\\bird.wav").c_str()); 

        Textures::background = LoadTexture((IO::GetCurrentDir() + "\\assets\\background.png").c_str());
        Textures::people = RenderUtils::LoadPeople();
        Textures::house = LoadTexture((IO::GetCurrentDir()+ "\\assets\\house.png").c_str());
        Textures::city = LoadTexture((IO::GetCurrentDir() + "\\assets\\city.png").c_str());
        Textures::metrocity = LoadTexture((IO::GetCurrentDir() + "\\assets\\metrocity.png").c_str());
        Textures::tree = LoadTexture((IO::GetCurrentDir() + "\\assets\\tree.png").c_str());
        Textures::grass = LoadTexture((IO::GetCurrentDir() + "\\assets\\grass.png").c_str());
        Textures::rock = LoadTexture((IO::GetCurrentDir() + "\\assets\\rock.png").c_str());
    }
}