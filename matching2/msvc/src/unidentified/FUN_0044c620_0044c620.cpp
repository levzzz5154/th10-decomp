#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C620..0x0044C62D: FUN_0044c620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c620_0044c620() {
    __asm {
    L_0044c620:
        mov dword ptr [eax+4],0
    L_0044c627:
        mov dword ptr [eax],3F800000h
    L_0044c62d:
        ret
    }
}
