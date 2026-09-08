#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E894..0x0045E8B3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045e894() {
    __asm {
    L_0045e894:
        xor eax,eax
    L_0045e896:
        mov ecx,dword ptr [eax*8+473C98h]
    L_0045e89d:
        cmp ecx,dword ptr [esp+4]
    L_0045e8a1:
        je short L_0045e8ac
    L_0045e8a3:
        inc eax
    L_0045e8a4:
        cmp eax,1Dh
    L_0045e8a7:
        jl short L_0045e896
    L_0045e8a9:
        xor eax,eax
    L_0045e8ab:
        ret
    L_0045e8ac:
        mov eax,dword ptr [eax*8+473C9Ch]
    L_0045e8b3:
        ret
    }
}
