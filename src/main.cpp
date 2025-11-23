/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "GameData.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"
#include "Input.hpp"
#include "SoundManager.hpp"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);

	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Simulace v2");

	InitAudioDevice();

	Renderer::InitRenderer();

	GameData::positionoffsets.resize(GameData::maxparticles, std::make_pair(0,0));
	GameData::ParticleList.resize(GameData::maxparticles, GameData::Particle{ {0,0}, 0, WHITE });

	GameData::positionoffsets.clear();
	GameData::ParticleList.clear();

	for (int i = 0; i < GameData::maxparticles; i++)
	{
	    float rx = (float)GetRandomValue(0, 800);  
	    float ry = (float)GetRandomValue(-480, 0); 

	    int vel = GetRandomValue(180, 350);      
	    Color col = (Color){ 65,83,105, 64 }; 

	    GameData::ParticleList.push_back({ {rx, ry}, vel, col });
	    GameData::positionoffsets.push_back({ 0, 0 });
	}

	SetExitKey(0);

	RenderTexture2D src = LoadRenderTexture(800, 480);

	SetTextureFilter(src.texture, TEXTURE_FILTER_POINT);

	Rectangle play = {
	    10, 40,
	    MeasureTextEx(GetFontDefault(), "Spustit Simulaci", 24, 0.5f).x,
	    60
	};
	Rectangle quit = {
	    10, 120,
	    MeasureTextEx(GetFontDefault(), "Ukoncit program", 24, 0.5f).x,
	    60
	};


	while (!WindowShouldClose() && !GameData::GameConfig::shouldexi)
	{
		Rectangle mouse = { GetMouseX() * (800.0f / GetScreenWidth()), GetMouseY() * (480.0f / GetScreenHeight()), 4, 4 };
		BeginTextureMode(src);

		switch (GameData::currentscene)
		{
			case GameData::Scene::loading:
        	    ClearBackground(BLACK);
				Renderer::RenderUtils::importpositions();
        	    break;
        	case GameData::Scene::menu:
				ClearBackground(BLACK);

				DrawTexturePro(
				    Renderer::Textures::background,
				    { 0, 0,
				      (float)Renderer::Textures::background.width,
				      (float)Renderer::Textures::background.height },
				    { 0, 0,
				      (float)src.texture.width,
				      (float)src.texture.height },
				    { 0, 0 },
				    0.0f,
				    WHITE
				);

				if (CheckCollisionRecs(mouse, play))
				{
				    DrawRectangleRec(play, {255,255,255,40});
				
				    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GameData::dataloaded)
				    {
				        GameData::currentscene = GameData::Scene::playing;
				    }
				}
				else
				{
				    DrawRectangleRec(play, {255,255,255,20});
				}

				if (CheckCollisionRecs(mouse, quit))
				{
				    DrawRectangleRec(quit, {255,255,255,40});
				
				    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				    {
				        GameData::GameConfig::shouldexi = true;
				    }
				}
				else
				{
				    DrawRectangleRec(quit, {255,255,255,20});
				}

				DrawTextEx(
				    GetFontDefault(),
				    "Spustit Simulaci",
				    {
				        play.x + (play.width  - MeasureTextEx(GetFontDefault(), "Spustit Simulaci", 18, 0.5f).x) / 2,
				        play.y + (play.height - MeasureTextEx(GetFontDefault(), "Spustit Simulaci", 18, 0.5f).y) / 2
				    },
				    18,
				    0.5f,
				    WHITE
				);

				DrawTextEx(
				    GetFontDefault(),
				    "Ukoncit program",
				    {
				        quit.x + (quit.width  - MeasureTextEx(GetFontDefault(), "Ukoncit program", 18, 0.5f).x) / 2,
				        quit.y + (quit.height - MeasureTextEx(GetFontDefault(), "Ukoncit program", 18, 0.5f).y) / 2
				    },
				    18,
				    0.5f,
				    WHITE
				);

				DrawText(
				    "ORIGINAL VYROBEN S RAYLIBEM C# || VERZE : 1.1 || SHADOWDEV 2024",
				    28,
				    (int)GameData::GameConfig::windowsize.y - 28,
				    20,
				    WHITE
				);

				DrawText(
				    "Simulace znecisteni",
				    (int)(GameData::GameConfig::windowsize.x / 2
				          - MeasureTextEx(GetFontDefault(), "Simulace znecisteni", 12, 0.5f).x),
				    28,
				    20,
				    WHITE
				);

				DrawText(
				    "ovladani:\nW,A,S,D (pohyb)\nE (posunout cas vpred o rok)",
				    (int)(GameData::GameConfig::windowsize.x / 2
				          - MeasureTextEx(GetFontDefault(), "crazy", 36, 0.5f).x),
				    96,
				    20,
				    WHITE
				);

				break;
        	case GameData::Scene::playing:
        	    ClearBackground(GREEN);
				Renderer::RenderUtils::rendermap();
				if (GameData::GameConfig::renderrainparticles) {
                    DrawRectangle(0,0,(int)GameData::GameConfig::windowsize.x,(int)GameData::GameConfig::windowsize.y, (Color){60,83,105,128});
                }else {
                    DrawRectangle(0,0,(int)GameData::GameConfig::windowsize.x,(int)GameData::GameConfig::windowsize.y,(Color){48,48,48,128});
                }
					if (GameData::GameConfig::renderrainparticles)
					{
						for (int i = 0; i < GameData::maxparticles; i++)
						{
						    GameData::ParticleList[i].position.y += GameData::ParticleList[i].velocity * GetFrameTime();
						
						    if (GameData::ParticleList[i].position.y > 480)
						    {
						        GameData::ParticleList[i].position.y = (float)GetRandomValue(-200, 0);
						        GameData::ParticleList[i].position.x = (float)GetRandomValue(0, 800);
						    }
						
						    DrawRectangle(
						        (int)GameData::ParticleList[i].position.x,
						        (int)GameData::ParticleList[i].position.y,
						        2,
						        12,
						        GameData::ParticleList[i].color
						    );
						}
					}else
					{
						for (int i = 0; i < GameData::maxparticles; i++)
						{
						    GameData::ParticleList[i].position.y += GameData::ParticleList[i].velocity * GetFrameTime();
						}
					}

				Renderer::RenderUtils::renderui();
        	    break;
        	case GameData::Scene::paused:
				{
				    ClearBackground(GREEN);
				    Renderer::RenderUtils::rendermap();
				
				    if (GameData::GameConfig::renderrainparticles) {
				        DrawRectangle(0,0,(int)GameData::GameConfig::windowsize.x,(int)GameData::GameConfig::windowsize.y, (Color){60,83,105,128});
				    } else {
				        DrawRectangle(0,0,(int)GameData::GameConfig::windowsize.x,(int)GameData::GameConfig::windowsize.y,(Color){48,48,48,128});
				    }
				
					if (GameData::GameConfig::renderrainparticles)
					{
						for (int i = 0; i < GameData::maxparticles; i++)
						{
						    if (GameData::ParticleList[i].position.y > 480)
						    {
						        GameData::ParticleList[i].position.y = (float)GetRandomValue(-200, 0);
						        GameData::ParticleList[i].position.x = (float)GetRandomValue(0, 800);
						    }
						
						    DrawRectangle(
						        (int)GameData::ParticleList[i].position.x,
						        (int)GameData::ParticleList[i].position.y,
						        2,
						        12,
						        GameData::ParticleList[i].color
						    );
						}
					}
				
				    Rectangle rec1 = {
				        30.0f,
				        GameData::GameConfig::windowsize.y * 0.8f,
				        200.0f,
				        60.0f
				    };
				
				    if (CheckCollisionRecs(mouse, rec1))
				    {
				        DrawText("Odejit", 30, (int)(rec1.y + rec1.height / 4), 20, WHITE);
				        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				            GameData::GameConfig::shouldexi = true;
				    }
				    else
				    {
				        DrawText("Odejit", 30, (int)(rec1.y + rec1.height / 4), 20, GRAY);
				    }
				
				    DrawText("PAUSED", 0, 0, 20, WHITE);
				}
				break;
        	case GameData::Scene::end:
        	    ClearBackground(BLACK);
				DrawTexturePro(
                    Renderer::Textures::background,
                    Rectangle{0, 0, (float)Renderer::Textures::background.width, (float)Renderer::Textures::background.height},
                    Rectangle{0, 0, GameData::GameConfig::windowsize.x, GameData::GameConfig::windowsize.y},
                    {0, 0},
                    0,
                    WHITE
                );

				Vector2 textSize = MeasureTextEx(GetFontDefault(),
				                                 "jezero bylo znecisteno",
				                                 22,
				                                 0.5f);

				DrawText("jezero bylo znecisteno",
				         (int)(GameData::GameConfig::windowsize.x / 2 - textSize.x / 2),
				         20,
				         22,
				         WHITE);

				std::string summary =
				    "jezero trvalo znecistit " + std::to_string((int)GameData::year) + " let\n"
				    "pobliz bylo " + std::to_string(GameData::bases.size()) + " vesnic/mest\n\n"
				    "simulace byla inspirovana hrou one chance\n"
				    "(az na to ze s ni nema nic spolecneho)\n\n"
				    "naprogramovano za 96 hodin\n\n"
				    "github @shadow9owo\n\n"
				    "http://shadowstudios.eu\n\n"
				    "#sh3d2024";
				
				textSize = MeasureTextEx(GetFontDefault(), summary.c_str(), 22, 0.5f);
				
				DrawText(summary.c_str(),
				         (int)(GameData::GameConfig::windowsize.x / 2 - textSize.x / 2),
				         96,
				         22,
				         WHITE);

				Rectangle rec = {
				    GameData::GameConfig::windowsize.x * 0.5f - 100.0f,
				    GameData::GameConfig::windowsize.y * 0.8f,
				    200.0f,
				    60.0f
				};

				if (CheckCollisionRecs(mouse, rec))
				{
				    DrawText("Odejit",
				             (int)(rec.x + rec.width / 4),
				             (int)(rec.y + rec.height / 4),
				             20,
				             WHITE);
					
				    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				        GameData::GameConfig::shouldexi = true;
				}
				else
				{
				    DrawText("Odejit",
				             (int)(rec.x + rec.width / 4),
				             (int)(rec.y + rec.height / 4),
				             20,
				             GRAY);
				}

        		break;
			default:
				break;
		}

		Input::handleinput();

		SoundManager::Soundmanagerfunc();

		EndTextureMode();

		ClearBackground(BLACK);

		BeginDrawing();

		DrawTexturePro(src.texture, {0,0,(float)src.texture.width,(float)-src.texture.height}, {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()}, {0,0},0.0f,WHITE);

		Logger::renderlogger();

		EndDrawing();
	}
	CloseAudioDevice();

	CloseWindow();
	return 0;
}
