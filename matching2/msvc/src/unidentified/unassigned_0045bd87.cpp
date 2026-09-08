#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD87..0x0045BD8F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045bd87() {
    __asm {
    L_0045bd87:
        lea esp,[esp+force_disp32_zero]
    L_0045bd8e:
        mov edi,edi
    }
}
