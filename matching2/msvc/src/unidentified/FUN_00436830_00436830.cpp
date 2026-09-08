#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436830..0x00436836: FUN_00436830
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436830_00436830() {
    __asm {
    L_00436830:
        mov eax,dword ptr [eax+110h]
    L_00436836:
        ret
    }
}
