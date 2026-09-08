#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424590..0x00424593: FUN_00424590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424590_00424590() {
    __asm {
    L_00424590:
        mov eax,dword ptr [eax+18h]
    L_00424593:
        ret
    }
}
