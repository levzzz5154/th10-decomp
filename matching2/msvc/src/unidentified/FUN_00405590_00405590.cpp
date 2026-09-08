#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405590..0x00405594: FUN_00405590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405590_00405590() {
    __asm {
    L_00405590:
        mov eax,dword ptr [eax+ecx*4+10h]
    L_00405594:
        ret
    }
}
