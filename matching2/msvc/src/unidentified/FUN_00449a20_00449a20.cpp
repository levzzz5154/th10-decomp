#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A20..0x00449A27: FUN_00449a20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449a20_00449a20() {
    __asm {
    L_00449a20:
        mov eax,dword ptr [ecx]
    L_00449a22:
        lea edx,[eax+1]
    L_00449a25:
        mov dword ptr [ecx],edx
    L_00449a27:
        ret
    }
}
