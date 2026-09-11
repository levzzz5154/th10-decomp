#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x0044FE40..0x0044FEF6: ?ECL_ResolveFloatOperand@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatOperand_0044fe40() {
    __asm {
    L_0044fe40:
        push ecx
    L_0044fe41:
        push esi
    L_0044fe42:
        push edi
    L_0044fe43:
        mov esi,eax
    L_0044fe45:
        mov edx,dword ptr [esi+4]
    L_0044fe48:
        movzx eax,word ptr [edx+8]
    L_0044fe4c:
        mov edi,1
    L_0044fe51:
        shl edi,cl
    L_0044fe53:
        test eax,edi
    L_0044fe55:
        je asm_target_0044feef
    L_0044fe5b:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe5f:
        fcomp dword ptr [data_00470b04]
    L_0044fe65:
        fnstsw ax
    L_0044fe67:
        test ah,1
    L_0044fe6a:
        jne short L_0044fe83
    L_0044fe6c:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe70:
        call asm_FUN_00463b2c_00463b2c
    L_0044fe75:
        add eax,dword ptr [esi+100Ch]
    L_0044fe7b:
        fld dword ptr [eax+esi+8]
    L_0044fe7f:
        pop edi
    L_0044fe80:
        pop esi
    L_0044fe81:
        pop ecx
    L_0044fe82:
        ret
    L_0044fe83:
        fld dword ptr [data_00470b60]
    L_0044fe89:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe8d:
        fucompp
    L_0044fe8f:
        fnstsw ax
    L_0044fe91:
        test ah,44h
    L_0044fe94:
        jp short L_0044fed4
    L_0044fe96:
        mov eax,dword ptr [esi+1008h]
    L_0044fe9c:
        add eax,0FFFFFFFCh
    L_0044fe9f:
        js short L_0044fecc
    L_0044fea1:
        mov dword ptr [esi+1008h],eax
    L_0044fea7:
        mov ecx,dword ptr [eax+esi+8]
    L_0044feab:
        add eax,0FFFFFFFCh
    L_0044feae:
        mov dword ptr [esi+1008h],eax
    L_0044feb4:
        mov al,byte ptr [eax+esi+8]
    L_0044feb8:
        cmp al,66h
    L_0044feba:
        mov dword ptr [esp+8],ecx
    L_0044febe:
        je short L_0044fecc
    L_0044fec0:
        cmp al,69h
    L_0044fec2:
        jne short L_0044fecc
    L_0044fec4:
        fild dword ptr [esp+8]
    L_0044fec8:
        pop edi
    L_0044fec9:
        pop esi
    L_0044feca:
        pop ecx
    L_0044fecb:
        ret
    L_0044fecc:
        fld dword ptr [esp+8]
    L_0044fed0:
        pop edi
    L_0044fed1:
        pop esi
    L_0044fed2:
        pop ecx
    L_0044fed3:
        ret
    L_0044fed4:
        mov esi,dword ptr [esi+1014h]
    L_0044feda:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fede:
        mov edi,dword ptr [esi]
    L_0044fee0:
        call asm_FUN_00463b2c_00463b2c
    L_0044fee5:
        push eax
    L_0044fee6:
        mov ecx,esi
    L_0044fee8:
        call dword ptr [edi+0Ch]
    L_0044feeb:
        pop edi
    L_0044feec:
        pop esi
    L_0044feed:
        pop ecx
    L_0044feee:
        ret
    L_0044feef:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fef3:
        pop edi
    L_0044fef4:
        pop esi
    L_0044fef5:
        pop ecx
    L_0044fef6:
        ret
    }
}
