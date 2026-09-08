#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405CB0..0x00405CB7: FUN_00405cb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405cb0_00405cb0() {
    __asm {
    L_00405cb0:
        mov eax,dword ptr [eax*4+474170h]
    L_00405cb7:
        ret
    }
}
