#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C230..0x0043C2B4: FUN_0043c230
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c230_0043c230() {
    __asm {
    L_0043c230:
        push ecx
    L_0043c231:
        mov eax,dword ptr [data_004918a4]
    L_0043c236:
        test eax,eax
    L_0043c238:
        push esi
    L_0043c239:
        mov esi,ecx
    L_0043c23b:
        jne short L_0043c285
    L_0043c23d:
        push edi
    L_0043c23e:
        mov edi,dword ptr [esi+1Ch]
    L_0043c241:
        test edi,edi
    L_0043c243:
        mov dword ptr [esp+8],edi
    L_0043c247:
        je short L_0043c27a
    L_0043c249:
        cmp dword ptr [esi+34h],edi
    L_0043c24c:
        jge short L_0043c265
    L_0043c24e:
        fld dword ptr [esi+38h]
    L_0043c251:
        fmul dword ptr [data_00470bf8]
    L_0043c257:
        fidiv dword ptr [esp+8]
    L_0043c25b:
        call asm_FUN_00463b2c_00463b2c
    L_0043c260:
        mov dword ptr [esi+18h],eax
    L_0043c263:
        jmp short L_0043c26c
    L_0043c265:
        mov dword ptr [esi+18h],0FFh
    L_0043c26c:
        mov eax,dword ptr [esi+18h]
    L_0043c26f:
        test eax,eax
    L_0043c271:
        jge short L_0043c27a
    L_0043c273:
        mov dword ptr [esi+18h],0
    L_0043c27a:
        mov eax,dword ptr [esi+34h]
    L_0043c27d:
        add edi,2
    L_0043c280:
        cmp eax,edi
    L_0043c282:
        pop edi
    L_0043c283:
        jl short L_0043c28d
    L_0043c285:
        mov eax,7
    L_0043c28a:
        pop esi
    L_0043c28b:
        pop ecx
    L_0043c28c:
        ret
    L_0043c28d:
        mov eax,dword ptr [data_00477810]
    L_0043c292:
        test eax,eax
    L_0043c294:
        je short L_0043c2a5
    L_0043c296:
        mov eax,dword ptr [eax+58h]
    L_0043c299:
        mov ecx,eax
    L_0043c29b:
        shr ecx,2
    L_0043c29e:
        or ecx,eax
    L_0043c2a0:
        test cl,1
    L_0043c2a3:
        jne short L_0043c2ad
    L_0043c2a5:
        add esi,30h
    L_0043c2a8:
        call asm_FrameTimer_Tick_00404ed0
    L_0043c2ad:
        mov eax,1
    L_0043c2b2:
        pop esi
    L_0043c2b3:
        pop ecx
    L_0043c2b4:
        ret
    }
}
