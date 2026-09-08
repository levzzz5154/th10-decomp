#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F80..0x00401F87: FUN_00401f80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401f80_00401f80() {
    __asm {
    L_00401f80:
        mov dword ptr [eax+24h],0
    L_00401f87:
        ret
    }
}
