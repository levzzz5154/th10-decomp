#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3001): closest_byte_count=260/260; first_diff=none
// (authoritative probe exact).  The exact member remains intact; readable
// output needs the EAX receiver, EBX point pointer, and private helper ABIs.
// variants_tested=retail inline-assembly member only; no failed source
// variant retained.  next_lever=schema2 native-LTCG cluster over real callers
// FUN_00425730, FUN_0040E770, DrawPlayer and callees 00408030/0041BB00
// (with 004086B0), preserving the EAX/EBX live-ins before cutover.
// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.

// 0x00408100..0x00408203: FUN_00408100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408100_00408100() {
    __asm {
    L_00408100:
        sub esp,18h
    L_00408103:
        push ebp
    L_00408104:
        push esi
    L_00408105:
        mov esi,eax
    L_00408107:
        push edi
    L_00408108:
        add esi,60h
    L_0040810b:
        mov ebp,7D0h
    L_00408110:
        mov ax,word ptr [esi+446h]
    L_00408117:
        test ax,ax
    L_0040811a:
        je asm_target_004081ec
    L_00408120:
        cmp ax,3
    L_00408124:
        je asm_target_004081ec
    L_0040812a:
        mov eax,dword ptr [esp+30h]
    L_0040812e:
        test eax,eax
    L_00408130:
        je short L_0040813d
    L_00408132:
        mov eax,dword ptr [esi+4]
    L_00408135:
        test eax,eax
    L_00408137:
        jne asm_target_004081ec
    L_0040813d:
        fld dword ptr [esi+3B4h]
    L_00408143:
        lea edi,[esi+3B4h]
    L_00408149:
        fsub dword ptr [ebx]
    L_0040814b:
        fstp dword ptr [esp+18h]
    L_0040814f:
        mov eax,dword ptr [esp+18h]
    L_00408153:
        fld dword ptr [esi+3B8h]
    L_00408159:
        mov dword ptr [esp+0Ch],eax
    L_0040815d:
        fsub dword ptr [ebx+4]
    L_00408160:
        fstp dword ptr [esp+1Ch]
    L_00408164:
        mov ecx,dword ptr [esp+1Ch]
    L_00408168:
        fld dword ptr [esi+3BCh]
    L_0040816e:
        mov dword ptr [esp+10h],ecx
    L_00408172:
        fsub dword ptr [ebx+8]
    L_00408175:
        fstp dword ptr [esp+20h]
    L_00408179:
        mov edx,dword ptr [esp+20h]
    L_0040817d:
        fld dword ptr [esi+3F0h]
    L_00408183:
        mov dword ptr [esp+14h],edx
    L_00408187:
        fmul dword ptr [data_00470b0c]
    L_0040818d:
        fadd dword ptr [esp+28h]
    L_00408191:
        fld dword ptr [esp+10h]
    L_00408195:
        fmul dword ptr [esp+10h]
    L_00408199:
        fld dword ptr [esp+0Ch]
    L_0040819d:
        fmul dword ptr [esp+0Ch]
    L_004081a1:
        faddp st(1),st
    L_004081a3:
        fld st(1)
    L_004081a5:
        fmul st,st(2)
    L_004081a7:
        fcompp
    L_004081a9:
        fnstsw ax
    L_004081ab:
        fstp st(0)
    L_004081ad:
        test ah,5
    L_004081b0:
        jnp short L_004081ec
    L_004081b2:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_004081b7:
        push 40000000h
    L_004081bc:
        push 40000000h
    L_004081c1:
        mov ecx,edi
    L_004081c3:
        call asm_OutsideAxisAlignedBounds_004086b0
    L_004081c8:
        test eax,eax
    L_004081ca:
        jne short L_004081ec
    L_004081cc:
        mov eax,dword ptr [esp+2Ch]
    L_004081d0:
        test eax,eax
    L_004081d2:
        je short L_004081ec
    L_004081d4:
        mov eax,dword ptr [data_00477818]
    L_004081d9:
        push 3F19999Ah
    L_004081de:
        push 0BFC90FDBh
    L_004081e3:
        push 0FFFFFFFFh
    L_004081e5:
        push 8
    L_004081e7:
        call asm_FUN_0041bb00_0041bb00
    L_004081ec:
        add esi,7F0h
    L_004081f2:
        dec ebp
    L_004081f3:
        jne asm_target_00408110
    L_004081f9:
        pop edi
    L_004081fa:
        pop esi
    L_004081fb:
        xor eax,eax
    L_004081fd:
        pop ebp
    L_004081fe:
        add esp,18h
    L_00408201:
        ret 0Ch
    }
}
