#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C890..0x0040C892: FUN_0040c890
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c890_0040c890() {
    __asm {
    L_0040c890:
        mov eax,dword ptr [eax]
    L_0040c892:
        ret
    }
}
