#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004175E0..0x004175FF: FUN_004175e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004175e0_004175e0() {
    __asm {
    L_004175e0:
        mov ecx,dword ptr [eax+3Ch]
    L_004175e3:
        cmp ecx,7
    L_004175e6:
        jge short L_004175ec
    L_004175e8:
        inc ecx
    L_004175e9:
        mov dword ptr [eax+3Ch],ecx
    L_004175ec:
        mov eax,dword ptr [eax+3Ch]
    L_004175ef:
        lea eax,[eax+eax*2]
    L_004175f2:
        shl eax,4
    L_004175f5:
        add eax,474788h
    L_004175fa:
        mov dword ptr [data_00477848],eax
    L_004175ff:
        ret
    }
}
