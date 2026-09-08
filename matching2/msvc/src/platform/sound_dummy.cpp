#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420B10..0x00420B58: Sound_PlayDummyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Sound_PlayDummyRetail_00420b10() {
    __asm {
    L_00420b10:
        test byte ptr [data_00491d78],10h
    L_00420b17:
        je short L_00420b2c
    L_00420b19:
        push 0
    L_00420b1b:
        push 4
    L_00420b1d:
        mov edx,46DF98h
    L_00420b22:
        mov eax,492590h
    L_00420b27:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420b2c:
        mov eax,dword ptr [esp+4]
    L_00420b30:
        push eax
    L_00420b31:
        push 2
    L_00420b33:
        mov edx,46DF98h
    L_00420b38:
        mov eax,492590h
    L_00420b3d:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420b42:
        mov ecx,dword ptr [data_0047783c]
    L_00420b48:
        mov edx,dword ptr [esp+8]
    L_00420b4c:
        mov byte ptr [ecx+edx+1D892h],1
    L_00420b54:
        xor eax,eax
    L_00420b56:
        ret 8
    }
}
