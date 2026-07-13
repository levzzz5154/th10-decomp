#include "th10/audio.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

namespace th10 {

bool AudioEngine::init(const char* game_path) {
    game_path_ = game_path;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "[audio] SDL_INIT_AUDIO failed: %s\n", SDL_GetError());
        return false;
    }

    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        fprintf(stderr, "[audio] Mix_Init failed: %s\n", Mix_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "[audio] Mix_OpenAudio failed: %s\n", Mix_GetError());
        return false;
    }

    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    printf("[audio] AudioEngine initialized (44100 Hz, stereo)\n");
    return true;
}

void AudioEngine::shutdown() {
    stop_bgm();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    printf("[audio] AudioEngine shutdown\n");
}

void AudioEngine::play_bgm(const char* path) {
    if (!path || !game_path_) return;

    if (bgm_opened_ && strcmp(current_bgm_path_, path) == 0) {
        if (!Mix_PlayingMusic()) {
            Mix_PlayMusic(nullptr, -1);
        }
        return;
    }

    stop_bgm();

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", game_path_, path);

    Mix_Music* music = Mix_LoadMUS(full_path);
    if (!music) {
        fprintf(stderr, "[audio] Cannot load BGM: %s (%s)\n", full_path, Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(music, -1) < 0) {
        fprintf(stderr, "[audio] Cannot play BGM: %s (%s)\n", full_path, Mix_GetError());
        Mix_FreeMusic(music);
        return;
    }

    strncpy(current_bgm_path_, path, sizeof(current_bgm_path_) - 1);
    bgm_opened_ = true;
    printf("[audio] Playing BGM: %s\n", path);
}

void AudioEngine::stop_bgm() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }

    if (bgm_opened_) {
        bgm_opened_ = false;
        current_bgm_path_[0] = '\0';
    }
    printf("[audio] BGM stopped\n");
}

void AudioEngine::fade_in_bgm(const char* path, int ms) {
    if (!path || !game_path_) return;

    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }

    if (bgm_opened_) {
        bgm_opened_ = false;
        current_bgm_path_[0] = '\0';
    }

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", game_path_, path);

    Mix_Music* music = Mix_LoadMUS(full_path);
    if (!music) {
        fprintf(stderr, "[audio] Cannot load BGM: %s (%s)\n", full_path, Mix_GetError());
        return;
    }

    Mix_VolumeMusic(0);

    if (Mix_FadeInMusic(music, -1, ms) < 0) {
        fprintf(stderr, "[audio] Cannot fade-in BGM: %s (%s)\n", full_path, Mix_GetError());
        Mix_FreeMusic(music);
        return;
    }

    strncpy(current_bgm_path_, path, sizeof(current_bgm_path_) - 1);
    bgm_opened_ = true;
    printf("[audio] Fading in BGM: %s (over %d ms)\n", path, ms);
}

void AudioEngine::set_volume(float vol) {
    if (vol < 0.0f) vol = 0.0f;
    if (vol > 1.0f) vol = 1.0f;
    int ivol = static_cast<int>(std::round(vol * MIX_MAX_VOLUME));
    Mix_VolumeMusic(ivol);
}

bool AudioEngine::is_playing() const {
    return Mix_PlayingMusic() != 0;
}

void AudioEngine::update() {
    if (bgm_opened_ && !Mix_PlayingMusic()) {
        bgm_opened_ = false;
        current_bgm_path_[0] = '\0';
    }
}

} // namespace th10
