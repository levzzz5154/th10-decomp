#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405150..0x00405153: FUN_00405150
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405150_00405150() {
    __asm {
    L_00405150:
        mov dword ptr [ecx+48h],eax
    L_00405153:
        ret
    }
}
