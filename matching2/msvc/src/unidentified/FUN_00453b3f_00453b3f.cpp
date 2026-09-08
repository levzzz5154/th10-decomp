#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453B3F..0x00453B53: FUN_00453b3f
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00453b3f_00453b3f() {
    __asm {
    L_00453b3f:
        push ebp
    L_00453b40:
        mov ebp,esp
    L_00453b42:
        mov eax,dword ptr [ebp+8]
    L_00453b45:
        push dword ptr [eax*8+473080h]
    L_00453b4c:
        call dword ptr [data_004660b4]
    L_00453b52:
        pop ebp
    L_00453b53:
        ret
    }
}
