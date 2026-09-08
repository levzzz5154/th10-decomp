#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462363..0x00462370: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462363() {
    __asm {
    L_00462363:
        cmp dword ptr [ecx+24h],10h
    L_00462367:
        jb short L_0046236d
    L_00462369:
        mov eax,dword ptr [ecx+10h]
    L_0046236c:
        ret
    L_0046236d:
        lea eax,[ecx+10h]
    L_00462370:
        ret
    }
}
