#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004187D0..0x004187EE: FUN_004187d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004187d0_004187d0() {
    __asm {
    L_004187d0:
        test byte ptr [ecx+58h],4
    L_004187d4:
        jne short L_004187e9
    L_004187d6:
        mov eax,dword ptr [data_00491c10]
    L_004187db:
        xor ecx,ecx
    L_004187dd:
        mov dword ptr [eax+50h],ecx
    L_004187e0:
        mov dword ptr [eax+54h],ecx
    L_004187e3:
        mov dword ptr [eax+4Ch],ecx
    L_004187e6:
        mov dword ptr [eax+58h],ecx
    L_004187e9:
        mov eax,1
    L_004187ee:
        ret
    }
}
