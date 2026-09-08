#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004658C0..0x004658E3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004658c0() {
    __asm {
    L_004658c0:
        mov eax,dword ptr [data_00474c64]
    L_004658c5:
        and eax,0FFFFFFFEh
    L_004658c8:
        test al,1
    L_004658ca:
        mov dword ptr [data_00474c64],eax
    L_004658cf:
        jne short L_004658e3
    L_004658d1:
        or eax,1
    L_004658d4:
        mov dword ptr [data_00474c60],476F78h
    L_004658de:
        mov dword ptr [data_00474c64],eax
    L_004658e3:
        ret
    }
}
