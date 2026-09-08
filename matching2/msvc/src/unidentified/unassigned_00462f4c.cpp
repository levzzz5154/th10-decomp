#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462F4C..0x00462F7B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462f4c() {
    __asm {
    L_00462f4c:
        mov eax,dword ptr [eax]
    L_00462f4e:
        cmp dword ptr [eax],0E06D7363h
    L_00462f54:
        jne short L_00462f79
    L_00462f56:
        cmp dword ptr [eax+10h],3
    L_00462f5a:
        jne short L_00462f79
    L_00462f5c:
        mov ecx,dword ptr [eax+14h]
    L_00462f5f:
        cmp ecx,19930520h
    L_00462f65:
        je short L_00462f6f
    L_00462f67:
        cmp ecx,19930521h
    L_00462f6d:
        jne short L_00462f79
    L_00462f6f:
        cmp dword ptr [eax+1Ch],0
    L_00462f73:
        jne short L_00462f79
    L_00462f75:
        xor eax,eax
    L_00462f77:
        inc eax
    L_00462f78:
        ret
    L_00462f79:
        xor eax,eax
    L_00462f7b:
        ret
    }
}
