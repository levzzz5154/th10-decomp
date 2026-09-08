#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462F2B..0x00462F30: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462f2b() {
    __asm {
    L_00462f2b:
        mov ebx,dword ptr [ebp+8]
    L_00462f2e:
        mov esi,dword ptr [ebp-1Ch]
    }
}
