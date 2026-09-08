#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004464D0..0x004464F9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004464d0() {
    __asm {
    L_004464d0:
        test byte ptr [data_00491d78],1
    L_004464d7:
        je short L_004464f9
    L_004464d9:
        mov ecx,dword ptr [eax*4+46F288h]
    L_004464e0:
        cmp ecx,15h
    L_004464e3:
        je short L_004464f4
    L_004464e5:
        test ecx,ecx
    L_004464e7:
        je short L_004464f4
    L_004464e9:
        cmp ecx,14h
    L_004464ec:
        jne short L_004464f9
    L_004464ee:
        mov eax,3
    L_004464f3:
        ret
    L_004464f4:
        mov eax,5
    L_004464f9:
        ret
    }
}
