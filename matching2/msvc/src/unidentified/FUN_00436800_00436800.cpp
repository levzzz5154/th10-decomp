#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436800..0x00436806: FUN_00436800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436800_00436800() {
    __asm {
    L_00436800:
        mov eax,dword ptr [eax+120h]
    L_00436806:
        ret
    }
}
