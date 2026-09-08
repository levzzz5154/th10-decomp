#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004525D0..0x004525FD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004525d0() {
    __asm {
    L_004525d0:
        mov eax,dword ptr [ebp-14h]
    L_004525d3:
        mov dword ptr [ebp-1Ch],eax
    L_004525d6:
        mov eax,dword ptr [ebp-1Ch]
    L_004525d9:
        mov eax,dword ptr [eax]
    L_004525db:
        mov dword ptr [ebp-20h],eax
    L_004525de:
        mov eax,dword ptr [ebp-20h]
    L_004525e1:
        cmp dword ptr [eax],0E06D7363h
    L_004525e7:
        je short L_004525f9
    L_004525e9:
        mov dword ptr [ebp-24h],0
    L_004525f0:
        mov eax,dword ptr [ebp-24h]
    L_004525f3:
        ret
    L_004525f4:
        mov esp,dword ptr [ebp-18h]
    L_004525f7:
        TH10_REL8(0xeb, 0x004525f7, VA_asm_target_004525c4)
    L_004525f9:
        call asm_terminate_00455693
    }
}
