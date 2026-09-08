#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405580..0x00405586: FUN_00405580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405580_00405580() {
    __asm {
    L_00405580:
        mov eax,dword ptr [eax+3788h]
    L_00405586:
        ret
    }
}
