#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434BE0..0x00434BE7: FUN_00434be0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434be0_00434be0() {
    __asm {
    L_00434be0:
        mov eax,dword ptr [eax+ecx*4+3AD06Ch]
    L_00434be7:
        ret
    }
}
