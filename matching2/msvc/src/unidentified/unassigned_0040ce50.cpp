#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE50..0x0040CE60: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce50() {
    __asm {
    L_0040ce50:
        cmp eax,63h
    L_0040ce53:
        jle short L_0040ce5a
    L_0040ce55:
        mov eax,63h
    L_0040ce5a:
        mov dword ptr [ecx+9EC0h],eax
    L_0040ce60:
        ret
    }
}
