// 0x0043DA80, 44 bytes: start the music stream and publish a command only
// after nonnegative status. Retail takes manager in ESI and command on the
// stack (RET 4); this explicit stdcall candidate has two stack arguments.
#include "sound_wave_types.hpp"

extern "C" int __stdcall Sound_StartMusicCommand_0043da80(
        WaveSoundManager* manager, unsigned int command) {
    SoundStream* stream = manager->music_stream;
    if (!stream || SoundStream_Start_0044d440(stream, 0, 1) < 0)
        return -1;
    manager->music_command = command;
    return 0;
}
