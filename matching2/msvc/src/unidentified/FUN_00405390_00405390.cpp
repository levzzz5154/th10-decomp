#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405390..0x00405393: FUN_00405390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405390_00405390() {
    __asm {
    L_00405390:
        mov eax,dword ptr [eax+4]
    L_00405393:
        ret
    }
}
