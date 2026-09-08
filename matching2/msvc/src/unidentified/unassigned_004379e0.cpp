#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004379E0..0x004379FE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004379e0() {
    __asm {
    L_004379e0:
        push ecx
    L_004379e1:
        lea eax,[esp]
    L_004379e4:
        push eax
    L_004379e5:
        mov eax,dword ptr [data_00491c30]
    L_004379ea:
        push 1
    L_004379ec:
        push 19h
    L_004379ee:
        push 0
    L_004379f0:
        push 1
    L_004379f2:
        push ecx
    L_004379f3:
        push edx
    L_004379f4:
        push eax
    L_004379f5:
        call asm_D3DXCreateTexture_004521a0
    L_004379fa:
        mov eax,dword ptr [esp]
    L_004379fd:
        pop ecx
    L_004379fe:
        ret
    }
}
