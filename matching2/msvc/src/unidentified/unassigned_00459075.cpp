#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459075..0x0045909E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00459075() {
    __asm {
    L_00459075:
        mov ecx,dword ptr [esp+4]
    L_00459079:
        xor eax,eax
    L_0045907b:
        cmp ecx,dword ptr [eax*8+473670h]
    L_00459082:
        je short L_0045908a
    L_00459084:
        inc eax
    L_00459085:
        cmp eax,13h
    L_00459088:
        jb short L_0045907b
    L_0045908a:
        shl eax,3
    L_0045908d:
        cmp ecx,dword ptr [eax+473670h]
    L_00459093:
        jne short L_0045909c
    L_00459095:
        mov eax,dword ptr [eax+473674h]
    L_0045909b:
        ret
    L_0045909c:
        xor eax,eax
    L_0045909e:
        ret
    }
}
