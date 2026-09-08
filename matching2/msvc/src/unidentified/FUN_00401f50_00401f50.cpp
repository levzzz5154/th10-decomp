#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F50..0x00401F57: FUN_00401f50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401f50_00401f50() {
    __asm {
    L_00401f50:
        mov dword ptr [eax+44h],0
    L_00401f57:
        ret
    }
}
