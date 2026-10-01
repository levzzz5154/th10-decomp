#include "../../src/platform/sound_stream_start.cpp"
#include "sound_start_platform_run_interface_0044d300.cpp"
#include "sound_start_platform_find_available_0044d370.cpp"
#include "sound_start_platform_query_interfaces_0044d600.cpp"
#include "sound_start_platform_set_operation_deadline_0044d4e0.cpp"
#include "sound_start_sound_stream_fill_model.cpp"
#include "sound_start_sound_fill_rewind.cpp"
#include "sound_start_sound_fill_read.cpp"

#pragma code_seg(".text$01command")
struct SoundCommandManager {
    unsigned char reserved[0x5208];
    SoundStream* music_stream;
    unsigned int unknown520c;
    unsigned int music_command;
};
extern "C" __declspec(noinline) int __stdcall StartMusicCommand(SoundCommandManager* manager, unsigned int command) {
    SoundStream* stream = manager->music_stream;
    if (!stream || SoundStreamStart(stream, 0, 1) < 0) return -1;
    manager->music_command = command;
    return 0;
}
#pragma code_seg()
