#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404E90..0x00404EA0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404e90() {
    __asm {
    L_00404e90:
        mov edx,dword ptr [ecx+4]
    L_00404e93:
        mov ecx,dword ptr [esp+4]
    L_00404e97:
        xor eax,eax
    L_00404e99:
        cmp edx,ecx
    L_00404e9b:
        setge al
    L_00404e9e:
        ret 4
    }
}
