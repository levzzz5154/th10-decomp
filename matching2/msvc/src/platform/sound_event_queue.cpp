#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DD10..0x0043DDA4: FUN_0043dd10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043dd10_0043dd10() {
    __asm {
    L_0043dd10:
        fld dword ptr [esp+4]
    L_0043dd14:
        push ebp
    L_0043dd15:
        fmul dword ptr [data_00470b20]
    L_0043dd1b:
        movsx ebp,word ptr [ebx*8+4749CEh]
    L_0043dd23:
        push edi
    L_0043dd24:
        call asm_FUN_00463b2c_00463b2c
    L_0043dd29:
        xor ecx,ecx
    L_0043dd2b:
        lea edx,[esi+620h]
    L_0043dd31:
        mov edi,dword ptr [edx]
    L_0043dd33:
        test edi,edi
    L_0043dd35:
        jl short L_0043dd7a
    L_0043dd37:
        cmp edi,ebx
    L_0043dd39:
        je short L_0043dd49
    L_0043dd3b:
        inc ecx
    L_0043dd3c:
        add edx,4
    L_0043dd3f:
        cmp ecx,0Ch
    L_0043dd42:
        jl short L_0043dd31
    L_0043dd44:
        pop edi
    L_0043dd45:
        pop ebp
    L_0043dd46:
        ret 4
    L_0043dd49:
        mov edx,dword ptr [esi+ecx*4+650h]
    L_0043dd50:
        cmp edx,80h
    L_0043dd56:
        jge short L_0043dda0
    L_0043dd58:
        mov edi,ecx
    L_0043dd5a:
        shl edi,7
    L_0043dd5d:
        add edi,edx
    L_0043dd5f:
        mov dword ptr [esi+edi*4+680h],eax
    L_0043dd66:
        mov eax,dword ptr [esi+ecx*4+650h]
    L_0043dd6d:
        inc eax
    L_0043dd6e:
        pop edi
    L_0043dd6f:
        mov dword ptr [esi+ecx*4+650h],eax
    L_0043dd76:
        pop ebp
    L_0043dd77:
        ret 4
    L_0043dd7a:
        cmp ecx,0Ch
    L_0043dd7d:
        jge short L_0043dda0
    L_0043dd7f:
        mov edx,ecx
    L_0043dd81:
        shl edx,9
    L_0043dd84:
        mov dword ptr [esi+ecx*4+620h],ebx
    L_0043dd8b:
        mov dword ptr [esi+ebx*4+408h],ebp
    L_0043dd92:
        mov dword ptr [edx+esi+680h],eax
    L_0043dd99:
        inc dword ptr [esi+ecx*4+650h]
    L_0043dda0:
        pop edi
    L_0043dda1:
        pop ebp
    L_0043dda2:
        ret 4
    }
}
