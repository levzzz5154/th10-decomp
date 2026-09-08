#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417590..0x00417593: FUN_00417590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417590_00417590() {
    __asm {
    L_00417590:
        mov eax,dword ptr [eax+5Ch]
    L_00417593:
        ret
    }
}
