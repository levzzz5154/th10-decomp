#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BBF0..0x0043BBF3: FUN_0043bbf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bbf0_0043bbf0() {
    __asm {
    L_0043bbf0:
        mov eax,dword ptr [eax+0Ch]
    L_0043bbf3:
        ret
    }
}
