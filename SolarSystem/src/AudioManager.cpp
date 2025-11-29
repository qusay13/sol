#include "../include/AudioManager.h"
#include <stdio.h>

AudioManager::AudioManager() : music(NULL), initialized(false) {}

AudioManager::~AudioManager() {
    cleanup();
}

void AudioManager::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mixer Error: %s\n", Mix_GetError());
        return;
    }

    music = Mix_LoadMUS("interstellar.mp3");
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1);
    initialized = true;
}

void AudioManager::cleanup() {
    if (music) {
        Mix_FreeMusic(music);
        music = NULL;
    }
    if (initialized) {
        Mix_CloseAudio();
        SDL_Quit();
    }
}
