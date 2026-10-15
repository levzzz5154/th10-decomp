// Compiler context and ABI anchors only; none of these bytes enter the image.
// The stream start and everything it calls come from its own cluster driver.
#include "sound_start_context.cpp"
#include "../../src/core/sound/sound_start_music_command_0043da80.cpp"

#pragma code_seg(".text$19context")
extern "C" int __stdcall SoundStartMusicCommandContext_0043da80(
        SoundCommandManager_0043da80** managers, int count) {
    int failures = 0;
    for (int i = 0; i < count; ++i)
        failures += managers[i]->StartMusicCommand(i);
    return failures;
}
#pragma code_seg()
