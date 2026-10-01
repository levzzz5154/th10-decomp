// 0x0043DA80 (44 bytes): start the music stream and, once it is playing,
// publish the command that started it. A missing stream or a failed start
// returns -1 and leaves the command untouched.
//
// Native LTCG passes the manager in ESI; the command stays on the stack.
#include "th10/game/sound_start_context.hpp"

struct SoundCommandManager_0043da80 {
    unsigned char reserved_0000[0x5208];
    SoundStream* music_stream;                         // +0x5208
    unsigned int reserved_520c;
    unsigned int music_command;                        // +0x5210

    __declspec(noinline) int StartMusicCommand(unsigned int command);
};

extern "C" int __stdcall SoundStreamStart(SoundStream* stream, unsigned int priority,
                                          unsigned int flags);

#pragma code_seg(".text$01m_command")
int SoundCommandManager_0043da80::StartMusicCommand(unsigned int command) {
    SoundStream* stream = music_stream;
    if (!stream)
        return -1;
    if (SoundStreamStart(stream, 0, 1) < 0)
        return -1;
    music_command = command;
    return 0;
}
#pragma code_seg()
