#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409EB0..0x00409F05: FUN_00409eb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409eb0_00409eb0() {
    __asm {
    L_00409eb0:
        mov eax,dword ptr [esi+34h]
    L_00409eb3:
        test eax,eax
    L_00409eb5:
        je short L_00409f05
    L_00409eb7:
        mov eax,dword ptr [esi+38h]
    L_00409eba:
        push edi
    L_00409ebb:
        xor edi,edi
    L_00409ebd:
        test eax,eax
    L_00409ebf:
        jle short L_00409ee6
    L_00409ec1:
        mov eax,dword ptr [esi+34h]
    L_00409ec4:
        mov eax,dword ptr [eax+edi*4]
    L_00409ec7:
        test eax,eax
    L_00409ec9:
        je short L_00409ede
    L_00409ecb:
        push eax
    L_00409ecc:
        call asm_free_00452422
    L_00409ed1:
        mov ecx,dword ptr [esi+34h]
    L_00409ed4:
        add esp,4
    L_00409ed7:
        mov dword ptr [ecx+edi*4],0
    L_00409ede:
        mov eax,dword ptr [esi+38h]
    L_00409ee1:
        inc edi
    L_00409ee2:
        cmp edi,eax
    L_00409ee4:
        jl short L_00409ec1
    L_00409ee6:
        mov eax,dword ptr [esi+34h]
    L_00409ee9:
        test eax,eax
    L_00409eeb:
        pop edi
    L_00409eec:
        je short L_00409efe
    L_00409eee:
        push eax
    L_00409eef:
        call asm_free_00452422
    L_00409ef4:
        add esp,4
    L_00409ef7:
        mov dword ptr [esi+34h],0
    L_00409efe:
        mov dword ptr [esi+34h],0
    L_00409f05:
        ret
    }
}
