#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130E0..0x004130E9: FUN_004130e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004130e0_004130e0() {
    __asm {
    L_004130e0:
        mov eax,dword ptr [esp+4]
    L_004130e4:
        mov dword ptr [ecx+4],eax
    L_004130e7:
        ret 4
    }
}
