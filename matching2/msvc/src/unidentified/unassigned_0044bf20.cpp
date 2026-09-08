#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BF20..0x0044BF24: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bf20() {
    __asm {
    L_0044bf20:
        and dword ptr [eax+10h],0FFFFFFFEh
    L_0044bf24:
        ret
    }
}
