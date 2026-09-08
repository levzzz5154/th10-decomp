#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045989C..0x004598BB: __global_unwind2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_global_unwind2_0045989c() {
    __asm {
    L_0045989c:
        push ebp
    L_0045989d:
        mov ebp,esp
    L_0045989f:
        push ebx
    L_004598a0:
        push esi
    L_004598a1:
        push edi
    L_004598a2:
        push ebp
    L_004598a3:
        push 0
    L_004598a5:
        push 0
    L_004598a7:
        push 4598B4h
    L_004598ac:
        push dword ptr [ebp+8]
    L_004598af:
        call asm_RtlUnwind_0046263a
    L_004598b4:
        pop ebp
    L_004598b5:
        pop edi
    L_004598b6:
        pop esi
    L_004598b7:
        pop ebx
    L_004598b8:
        mov esp,ebp
    L_004598ba:
        pop ebp
    L_004598bb:
        ret
    }
}
