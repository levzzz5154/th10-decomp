#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FD1C..0x0045FD20: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fd1c() {
    __asm {
    L_0045fd1c:
        xor edi,edi
    L_0045fd1e:
        mov esi,dword ptr [ebp-20h]
    }
}
