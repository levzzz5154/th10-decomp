// Complete helper bodies preserve their actual private register contracts.
#include "../../../src/platform/sound_device_init.cpp"
#include "primary_format.cpp"
#include "wave_load.cpp"
#define code_seg(name) code_seg(".text$0043d250_fn")
#include "../sound_wave_load/chunks.cpp"
#undef code_seg
#pragma code_seg()
#define code_seg(name) code_seg(".text$0044b810_fn")
#include "../sound_wave_load/log.cpp"
#undef code_seg
#pragma code_seg()

#pragma code_seg(".text$0044ba00_context")
extern "C" int __stdcall SoundInitializeContext(WaveSoundManager* manager, void* window) {
    return manager->Initialize(window);
}
#pragma code_seg()
