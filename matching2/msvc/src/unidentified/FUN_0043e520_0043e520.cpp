#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E520..0x0043E526: FUN_0043e520
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043e520_0043e520() {
    __asm {
    L_0043e520:
        mov eax,dword ptr [eax+90h]
    L_0043e526:
        ret
    }
}
