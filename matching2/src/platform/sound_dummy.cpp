#include "th10/platform/sound_dummy.hpp"

extern uint8_t DAT_00491d78;    // device caps flags, bit 4 gates the pre-cue
extern uint8_t* DAT_0047783c;   // published progress block

// 0x00420B10 - Play the "dummy" cue and latch a progress byte. The
// retail thiscall context is threaded through unchanged (the decompiled
// extraout_ECX shuffle has no observable effect).
uint32_t Sound_PlayDummy(void* context, uint32_t argument, int32_t slot,
                         void (*play)(void* context, const char* name,
                                      int32_t mode, uint32_t value)) {
    if ((DAT_00491d78 & 0x10u) != 0 && play != 0) {
        play(context, "dummy", 4, 0);
    }
    if (play != 0) {
        play(context, "dummy", 2, argument);
    }
    DAT_0047783c[0x1D892 + slot] = 1;
    return 0;
}
