#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DDB0..0x0043DDE3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043ddb0() {
    __asm {
    L_0043ddb0:
        xor eax,eax
    L_0043ddb2:
        lea ecx,[esi+620h]
    L_0043ddb8:
        mov edx,dword ptr [ecx]
    L_0043ddba:
        test edx,edx
    L_0043ddbc:
        jl short L_0043ddcc
    L_0043ddbe:
        cmp edx,edi
    L_0043ddc0:
        je short L_0043ddd8
    L_0043ddc2:
        inc eax
    L_0043ddc3:
        add ecx,4
    L_0043ddc6:
        cmp eax,0Ch
    L_0043ddc9:
        jl short L_0043ddb8
    L_0043ddcb:
        ret
    L_0043ddcc:
        cmp eax,0Ch
    L_0043ddcf:
        jge short L_0043dde3
    L_0043ddd1:
        mov dword ptr [esi+eax*4+620h],edi
    L_0043ddd8:
        mov dword ptr [esi+eax*4+650h],0FFFFFFFFh
    L_0043dde3:
        ret
    }
}
