#include "raylib.h"
#include "Input.hpp"
#include "GameData.hpp"
#include "Utils.hpp"
#include "raymath.h"
#include <iostream>
#include "Simulation.hpp"

namespace Input
{
    float timer = 0;

    void handleinput() 
    {
        if (GameData::currentscene == GameData::Scene::menu || GameData::currentscene == GameData::Scene::loading) return;
        if (IsKeyPressed(KEY_ESCAPE)) 
        {
            if (GameData::currentscene == GameData::Scene::paused) {
                GameData::currentscene = GameData::Scene::playing;
                GameData::GameConfig::timescale = 1;
            }else if (GameData::currentscene != GameData::Scene::menu) {
                GameData::GameConfig::timescale = 0;
                GameData::currentscene = GameData::Scene::paused;
            }
        }
        if (IsKeyPressed(KEY_F3)) {
            GameData::GameConfig::debug = !GameData::GameConfig::debug;
        }
        if (GameData::currentscene == GameData::Scene::playing)
        {
            float dt = GetFrameTime();
            float speed = 200.0f;
        
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
                GameData::position.y += speed * dt;
        
            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
                GameData::position.y -= speed * dt;
        
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
                GameData::position.x += speed * dt;
        
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
                GameData::position.x -= speed * dt;
        
            GameData::position.x = Utils::Clamp(GameData::position.x, -1024, 1024);
            GameData::position.y = Utils::Clamp(GameData::position.y, -1024, 1024);
        }
        if (IsKeyPressed(KEY_E)) 
        {
            Simulation::fastforward();
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (GameData::GameConfig::debug)
            {
                Vector2 mouse = GetMousePosition();
                Vector2 sub = Vector2Subtract(mouse, GameData::position);
                Vector2 add = Vector2Add(mouse, GameData::position);

                std::cout << sub.x << "," << add.y << std::endl;
            }
        }
        return;
    }
}