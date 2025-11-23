#include "SoundManager.hpp"
#include "GameData.hpp"
#include "raylib.h"
#include "Renderer.hpp"

namespace SoundManager
{
    float volume = 1.0f;

    void Soundmanagerfunc() {
        if (GameData::currentscene != GameData::Scene::playing) 
        {
            StopSound(Renderer::Sounds::bird);
            StopSound(Renderer::Sounds::rain);
        }
        else
        {
            SetSoundVolume(Renderer::Sounds::bird, volume);
            SetSoundVolume(Renderer::Sounds::rain, volume);

            if (!IsSoundPlaying(Renderer::Sounds::bird)) {
                PlaySound(Renderer::Sounds::bird);
            }

            if (GameData::GameConfig::renderrainparticles) {
                if (!IsSoundPlaying(Renderer::Sounds::rain)) {
                    PlaySound(Renderer::Sounds::rain);
                }
            }
            else
            {
                StopSound(Renderer::Sounds::rain);
            }
        }
        return;
    }
}
