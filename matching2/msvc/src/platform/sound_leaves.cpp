#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// 0x00420C30..0x00420C83: Sound_PlayRandomVoiceRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Sound_PlayRandomVoiceRetail_00420c30() {
    __asm {
    L_00420c30:
        fld dword ptr [data_00470b04]
    L_00420c36:
        fld dword ptr [data_00476f78]
    L_00420c3c:
        fucompp
    L_00420c3e:
        fnstsw ax
    L_00420c40:
        test ah,44h
    L_00420c43:
        jp short L_00420c4b
    L_00420c45:
        fld dword ptr [esp+4]
    L_00420c49:
        jmp short L_00420c68
    L_00420c4b:
        fld dword ptr [data_00476f78]
    L_00420c51:
        fcomp dword ptr [data_00470afc]
    L_00420c57:
        fld dword ptr [esp+4]
    L_00420c5b:
        fnstsw ax
    L_00420c5d:
        test ah,41h
    L_00420c60:
        je short L_00420c68
    L_00420c62:
        fdiv dword ptr [data_00476f78]
    L_00420c68:
        call asm_FUN_00463b2c_00463b2c
    L_00420c6d:
        push eax
    L_00420c6e:
        push 5
    L_00420c70:
        mov edx,46D275h
    L_00420c75:
        mov eax,492590h
    L_00420c7a:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c7f:
        xor eax,eax
    L_00420c81:
        ret 4
    }
}

// 0x0044D730..0x0044D73A: restore the derived vtable, then let the shared
// owned-array base destructor release the DirectSound buffers.
void __fastcall SoundBuffer_DestructBaseRetail(SoundBuffer* sound_buffer) {
    sound_buffer->vtable = &sound_buffer_vtable_004705d4;
    Platform_ReleaseOwnedArray(sound_buffer);
}
