#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager {
private:
    Mix_Music* music;
    bool initialized;

public:
    AudioManager();
    ~AudioManager();
    void init();
    void cleanup();
};

#endif
