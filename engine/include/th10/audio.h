#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdint>

namespace th10 {

enum class BgmMode {
    Preload = 0,   // FUN_0043e460 mode 0: BGM preload
    Play    = 1,   // FUN_0043e460 mode 1: BGM play (stage music)
    Stage   = 2,   // FUN_0043e460 mode 2: BGM with stage index
    Stop    = 3,   // FUN_0043e460 mode 3: BGM stop
    Silence = 4,   // FUN_0043e460 mode 4: silence/dummy cleanup
    FadeIn  = 5,   // FUN_0043e460 mode 5: BGM fade-in
};

class AudioEngine {
public:
    AudioEngine() = default;
    ~AudioEngine() = default;

    bool init(const char* game_path);
    void shutdown();

    void play_bgm(const char* path);
    void stop_bgm();
    void fade_in_bgm(const char* path, int ms = 2000);
    void set_volume(float vol);
    bool is_playing() const;

    void update();

private:
    bool bgm_opened_ = false;
    char current_bgm_path_[512] = {};
    const char* game_path_ = nullptr;
};

} // namespace th10
