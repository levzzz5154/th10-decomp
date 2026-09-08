#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C680..0x0040C687: FUN_0040c680
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c680_0040c680() {
    __asm {
    L_0040c680:
        mov eax,dword ptr [edx+4]
    L_0040c683:
        jmp asm_ECL_ResolveFloatValue_0044ff80
    }
}
