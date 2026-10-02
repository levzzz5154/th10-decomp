// Music_Play: queue a music-slot play request and unlock its music-room entry.
// Native-LTCG residual (2026-10-02): closest_byte_count=63/73;
// first_diff=0x00420B43. Both RegisterResource calls reproduce the private
// EAX/EDX convention. Only the final indexed store differs: C++ loads the
// heard index into ECX before loading the progress pointer into EDX, while
// retail loads the pointer into ECX and then the index into EDX.
// Ghidra disassembly and seven real callers confirm two stack arguments and
// RET 8; incoming ECX is unused. The decompiler's thiscall receiver is spurious.
// Ordinary member setters/getters, char/bool and signed/unsigned types, byte
// memcpy/memset, integer/pointer address expressions, and separate-TU helpers
// inlined by native LTCG all retain the same 73-byte residual. A schema-2
// cluster with real music-request callers and the registrar does too.
// Proof: build/experiments/music_play_tail_20261002/NOTES.txt.

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
