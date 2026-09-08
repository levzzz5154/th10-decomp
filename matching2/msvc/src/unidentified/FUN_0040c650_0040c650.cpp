#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C650..0x0040C657: FUN_0040c650
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c650_0040c650() {
    __asm {
    L_0040c650:
        mov eax,dword ptr [eax+4]
    L_0040c653:
        jmp asm_ECL_ResolveFloatOperand_0044fe40
    }
}
