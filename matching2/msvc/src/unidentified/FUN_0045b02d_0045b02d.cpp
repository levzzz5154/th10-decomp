#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B02D..0x0045B032: FUN_0045b02d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045b02d_0045b02d() {
    __asm {
    L_0045b02d:
        mov eax,dword ptr [data_00473ad4]
    L_0045b032:
        ret
    }
}
