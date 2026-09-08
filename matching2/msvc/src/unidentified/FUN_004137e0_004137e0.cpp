#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004137E0..0x004137E3: FUN_004137e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004137e0_004137e0() {
    __asm {
    L_004137e0:
        mov eax,dword ptr [eax+10h]
    L_004137e3:
        ret
    }
}
