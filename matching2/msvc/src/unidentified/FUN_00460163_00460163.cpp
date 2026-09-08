#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460163..0x0046016F: FUN_00460163
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00460163_00460163() {
    __asm {
    L_00460163:
        cmp dword ptr [ebp-1Ch],ecx
    L_00460166:
        je short L_0046016f
    L_00460168:
        push ecx
    L_00460169:
        call asm_FUN_00453b3f_00453b3f
    L_0046016e:
        pop ecx
    L_0046016f:
        ret
    }
}
