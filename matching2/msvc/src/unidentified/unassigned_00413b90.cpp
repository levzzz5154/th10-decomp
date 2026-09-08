#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413B90..0x00413BBE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413b90() {
    __asm {
    L_00413b90:
        push esi
    L_00413b91:
        mov esi,dword ptr [data_00491c10]
    L_00413b97:
        add esi,3AD084h
    L_00413b9d:
        push edi
    L_00413b9e:
        mov edi,dword ptr [esi]
    L_00413ba0:
        test edi,edi
    L_00413ba2:
        je short L_00413bba
    L_00413ba4:
        call asm_FUN_00447810_00447810
    L_00413ba9:
        mov eax,dword ptr [esi]
    L_00413bab:
        push eax
    L_00413bac:
        call asm_free_004524a1
    L_00413bb1:
        add esp,4
    L_00413bb4:
        mov dword ptr [esi],0
    L_00413bba:
        pop edi
    L_00413bbb:
        xor eax,eax
    L_00413bbd:
        pop esi
    L_00413bbe:
        ret
    }
}
