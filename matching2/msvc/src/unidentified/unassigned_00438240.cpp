#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438240..0x0043824D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438240() {
    __asm {
    L_00438240:
        cmp dword ptr [eax+18h],10h
    L_00438244:
        jb short L_0043824a
    L_00438246:
        mov eax,dword ptr [eax+4]
    L_00438249:
        ret
    L_0043824a:
        add eax,4
    L_0043824d:
        ret
    }
}
