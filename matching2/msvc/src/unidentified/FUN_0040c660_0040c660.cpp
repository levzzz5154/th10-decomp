#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C660..0x0040C667: FUN_0040c660
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c660_0040c660() {
    __asm {
    L_0040c660:
        mov eax,dword ptr [eax+4]
    L_0040c663:
        jmp asm_ECL_ResolveFloatDestination_00450070
    }
}
