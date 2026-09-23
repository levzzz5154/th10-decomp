#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BA30..0x0041BA4C: FUN_0041ba30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ba30_0041ba30() {
    __asm {
    L_0041ba30:
        mov edx,dword ptr [data_00477810]
    L_0041ba36:
        test edx,edx
    L_0041ba38:
        mov eax,ecx
    L_0041ba3a:
        je short L_0041ba48
    L_0041ba3c:
        test byte ptr [edx+58h],4
    L_0041ba40:
        je short L_0041ba48
    L_0041ba42:
        mov eax,1
    L_0041ba47:
        ret
    L_0041ba48:
        jmp asm_FUN_0041b8e0_0041b8e0
    }
}
