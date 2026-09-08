#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460C1E..0x00460C25: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00460c1e() {
    __asm {
    L_00460c1e:
        mov eax,dword ptr [esp+4]
    L_00460c22:
        add eax,20h
    L_00460c25:
        ret
    }
}
