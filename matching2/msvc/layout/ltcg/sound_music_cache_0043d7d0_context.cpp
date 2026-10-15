// Compiler context only; never selected as recovered game code.
#include "../../src/core/sound/sound_music_cache.cpp"

// The music command handler (0x0043DDF0) is the only caller: it hands over a
// command's slot and name from two places.
#pragma code_seg(".text$95context")
int __stdcall SoundMusicCacheContext(WaveSoundManager* manager, MusicCommand* command,
        Supervisor** supervisor) {
    *supervisor = &g_supervisor;
    if (g_supervisor.flags & 0x10) {
        if (command->step)
            return -1;
        manager->CacheMusic(command->argument, command->name);
        return 1;
    }
    manager->CacheMusic(command->argument, command->name);
    return 1;
}
#pragma code_seg()
