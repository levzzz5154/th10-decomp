#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F60..0x00401F67: FUN_00401f60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401f60_00401f60() {
    __asm {
    L_00401f60:
        mov dword ptr [eax+34h],0
    L_00401f67:
        ret
    }
}
