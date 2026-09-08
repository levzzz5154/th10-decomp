#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176D0..0x004176D2: FUN_004176d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004176d0_004176d0() {
    __asm {
    L_004176d0:
        mov eax,dword ptr [eax]
    L_004176d2:
        ret
    }
}
