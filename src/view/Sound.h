#include <string>
#include <map>

class Sound {
    public:
        std::string wavePath;
        std::string musicPath;
        Mix_Chunk *wave = NULL;
        Mix_Music *music = NULL;

    void load() {
        if (!wavePath.empty()) {
            // wave = Mix_LoadWAV(wavePath.c_str());
        } else if (!musicPath.empty()) {
            music = Mix_LoadMUS(musicPath.c_str());
        }
    }

    void play() {
        if (wave != nullptr) {
            // Mix_PlayChannel(-1, wave, 0);
        } else if (music != nullptr) {
            Mix_PlayMusic( music, -1);
        }
    }

    void pause() {
    }

    void stop() {
        Mix_FreeChunk(wave);
	    Mix_FreeMusic(music);
    }
};