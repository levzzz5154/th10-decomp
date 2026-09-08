#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004187A0..0x004187BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004187a0() {
    __asm {
    L_004187a0:
        test byte ptr [eax+58h],4
    L_004187a4:
        jne short L_004187b9
    L_004187a6:
        mov eax,dword ptr [data_00491c10]
    L_004187ab:
        xor ecx,ecx
    L_004187ad:
        mov dword ptr [eax+50h],ecx
    L_004187b0:
        mov dword ptr [eax+54h],ecx
    L_004187b3:
        mov dword ptr [eax+4Ch],ecx
    L_004187b6:
        mov dword ptr [eax+58h],ecx
    L_004187b9:
        mov eax,1
    L_004187be:
        ret
    }
}
