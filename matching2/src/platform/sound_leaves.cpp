#include "th10/platform/sound_leaves.hpp"

#ifdef _MSC_VER
extern "C" void sub_44D080(void**);
extern "C" float flt_470B04;
extern "C" float flt_470AFC;
extern "C" float flt_476F78;
extern "C" long __cdecl __ftol2(void);
extern "C" int sub_43E460(void*, const char*, int, int);
#endif

// 0x00420C30 - Play the random voice cue. The 64-bit random draw and
// the sound-play edge are injected; retail truncates the draw to its
// low 32 bits for the play argument.
#ifdef _MSC_VER
__declspec(naked) uint32_t Sound_PlayRandomVoiceRetail() {
    __asm {
        fld dword ptr [flt_470B04]
        fld dword ptr [flt_476F78]
        fucompp
        fnstsw ax
        test ah, 44h
        jp loc_420C4B
        fld dword ptr [esp+4]
        jmp loc_420C68
loc_420C4B:
        fld dword ptr [flt_476F78]
        fcomp dword ptr [flt_470AFC]
        fld dword ptr [esp+4]
        fnstsw ax
        test ah, 41h
        jz loc_420C68
        fdiv dword ptr [flt_476F78]
loc_420C68:
        call __ftol2
        push eax
        push 5
        mov edx, 46D275h
        mov eax, 492590h
        call sub_43E460
        xor eax, eax
        ret 4
    }
}
#endif

uint32_t Sound_PlayRandomVoice(uint64_t (*random)(),
                               void (*play)(const char* name, int32_t mode,
                                            int32_t value)) {
    const uint64_t value = random != 0 ? random() : 0;
    if (play != 0) {
        play("", 5, (int32_t)value);
    }
    return 0;
}

// 0x0044D730 - Sound-buffer destructor leaf. Retail overwrites the
// object's vtable slot with the base image at 0x004705D4 and tail-calls
// the shared release body at 0x0044D080.
#ifdef _MSC_VER
__declspec(naked) void SoundBuffer_DestructBaseRetail() {
    __asm {
        mov dword ptr [ecx], 4705D4h
        jmp sub_44D080
    }
}
#endif

void SoundBuffer_DestructBase(void** object, void (*release)(void** object)) {
    *object = (void*)&PTR_FUN_004705d4;
    if (release != 0) {
        release(object);
    }
}
