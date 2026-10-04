// Compiler context only; never selected as recovered game code.
#include "../../src/platform/sound_music_play_cached.cpp"

// The music command handler (0x0043DDF0) is the only caller.
#pragma code_seg(".text$95context")
int __stdcall SoundMusicPlayCachedContext(WaveSoundManager* manager, MusicCommand* command,
        Supervisor** supervisor) {
    *supervisor = &g_supervisor;
    if (command->argument < 0)
        return -1;
    if (command->step)
        return 1;
    if (manager->PlayCachedMusic(command->argument) == 0)
        return 2;
    return 0;
}
#pragma code_seg()
