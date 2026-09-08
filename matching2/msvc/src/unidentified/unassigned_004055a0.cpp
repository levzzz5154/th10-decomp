#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004055A0..0x004055BC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004055a0() {
    __asm {
    L_004055a0:
        and dword ptr [edx+24h],0FFFFFFFEh
    L_004055a4:
        push edi
    L_004055a5:
        xor eax,eax
    L_004055a7:
        mov ecx,12h
    L_004055ac:
        mov edi,edx
    L_004055ae:
        rep stosd
    L_004055b0:
        or dword ptr [edx],2
    L_004055b3:
        mov dword ptr [data_004776ec],edx
    L_004055b9:
        mov eax,edx
    L_004055bb:
        pop edi
    L_004055bc:
        ret
    }
}
