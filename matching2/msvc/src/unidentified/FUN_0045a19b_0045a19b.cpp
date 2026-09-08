#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A19B..0x0045A1A0: FUN_0045a19b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045a19b_0045a19b() {
    __asm {
    L_0045a19b:
        mov eax,dword ptr [data_004739d8]
    L_0045a1a0:
        ret
    }
}
