#include "th10/platform/sound_dummy.hpp"

#ifdef _MSC_VER
extern "C" int sub_43E460(void*, const char*, int, int);
#endif

extern uint8_t DAT_00491d78;    // device caps flags, bit 4 gates the pre-cue
extern uint8_t* DAT_0047783c;   // published progress block

// 0x00420B10 - Play the "dummy" cue and latch a progress byte. The
// retail thiscall context is threaded through unchanged (the decompiled
// extraout_ECX shuffle has no observable effect).
#ifdef _MSC_VER
__declspec(naked) uint32_t Sound_PlayDummyRetail() {
    __asm {
        test byte ptr [DAT_00491d78], 10h
        jz loc_420B2C
        push 0
        push 4
        mov edx, 46DF98h
        mov eax, 492590h
        call sub_43E460
loc_420B2C:
        mov eax, [esp+4]
        push eax
        push 2
        mov edx, 46DF98h
        mov eax, 492590h
        call sub_43E460
        mov ecx, dword ptr [DAT_0047783c]
        mov edx, [esp+8]
        mov byte ptr [ecx+edx+1D892h], 1
        xor eax, eax
        ret 8
    }
}
#endif

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
