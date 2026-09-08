#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408830..0x00408834: FUN_00408830
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408830_00408830() {
    __asm {
    L_00408830:
        mov eax,dword ptr [eax+ecx*4+30h]
    L_00408834:
        ret
    }
}
