// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sound/sound_music_commands.cpp"

// The frame loop and the shutdown path each run the queue on the one manager.
#pragma code_seg(".text$a95context")
unsigned int __stdcall SoundMusicCommandsContext(Supervisor** supervisor, int drain) {
    *supervisor = &g_supervisor;
    if (drain)
        return g_wave_sound_manager.ProcessCommands();
    g_wave_sound_manager.ProcessCommands();
    return 0;
}
#pragma code_seg()
