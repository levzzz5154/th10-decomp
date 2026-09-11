#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413A20..0x00413B40: FUN_00413a20
// Naked body preserves the retail register/stack ABI.

// 0x0041C330..0x0041C441: FUN_0041c330
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c330_0041c330() {
    __asm {
    L_0041c330:
        push esi
    L_0041c331:
        mov esi,dword ptr [edi+18h]
    L_0041c334:
        test esi,esi
    L_0041c336:
        je asm_target_0041c43b
    L_0041c33c:
        push ebx
    L_0041c33d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041c340:
        mov al,byte ptr [esi+50h]
    L_0041c343:
        test al,al
    L_0041c345:
        mov ebx,dword ptr [esi+8]
    L_0041c348:
        je short L_0041c359
    L_0041c34a:
        inc al
    L_0041c34c:
        cmp al,2
    L_0041c34e:
        mov byte ptr [esi+50h],al
    L_0041c351:
        jb short L_0041c359
    L_0041c353:
        mov eax,dword ptr [esi]
    L_0041c355:
        mov ecx,esi
    L_0041c357:
        jmp short L_0041c363
    L_0041c359:
        cmp dword ptr [esi+0Ch],1
    L_0041c35d:
        mov eax,dword ptr [esi]
    L_0041c35f:
        mov ecx,esi
    L_0041c361:
        jne short L_0041c3a1
    L_0041c363:
        call dword ptr [eax+10h]
    L_0041c366:
        dec dword ptr [edi+438h]
    L_0041c36c:
        mov edx,dword ptr [esi+8]
    L_0041c36f:
        mov ecx,dword ptr [esi+4]
    L_0041c372:
        mov dword ptr [ecx+8],edx
    L_0041c375:
        mov eax,dword ptr [esi+8]
    L_0041c378:
        test eax,eax
    L_0041c37a:
        je short L_0041c382
    L_0041c37c:
        mov ecx,dword ptr [esi+4]
    L_0041c37f:
        mov dword ptr [eax+4],ecx
    L_0041c382:
        cmp dword ptr [edi+434h],esi
    L_0041c388:
        jne short L_0041c393
    L_0041c38a:
        mov edx,dword ptr [esi+4]
    L_0041c38d:
        mov dword ptr [edi+434h],edx
    L_0041c393:
        push esi
    L_0041c394:
        call asm_free_004524a1
    L_0041c399:
        add esp,4
    L_0041c39c:
        jmp asm_target_0041c430
    L_0041c3a1:
        call dword ptr [eax+8]
    L_0041c3a4:
        test eax,eax
    L_0041c3a6:
        je short L_0041c3e7
    L_0041c3a8:
        mov edx,dword ptr [esi]
    L_0041c3aa:
        mov ecx,esi
    L_0041c3ac:
        call dword ptr [edx+10h]
    L_0041c3af:
        dec dword ptr [edi+438h]
    L_0041c3b5:
        mov eax,dword ptr [esi+4]
    L_0041c3b8:
        mov ecx,dword ptr [esi+8]
    L_0041c3bb:
        mov dword ptr [eax+8],ecx
    L_0041c3be:
        mov eax,dword ptr [esi+8]
    L_0041c3c1:
        test eax,eax
    L_0041c3c3:
        je short L_0041c3cb
    L_0041c3c5:
        mov edx,dword ptr [esi+4]
    L_0041c3c8:
        mov dword ptr [eax+4],edx
    L_0041c3cb:
        cmp dword ptr [edi+434h],esi
    L_0041c3d1:
        jne short L_0041c3dc
    L_0041c3d3:
        mov eax,dword ptr [esi+4]
    L_0041c3d6:
        mov dword ptr [edi+434h],eax
    L_0041c3dc:
        push esi
    L_0041c3dd:
        call asm_free_004524a1
    L_0041c3e2:
        add esp,4
    L_0041c3e5:
        jmp short L_0041c430
    L_0041c3e7:
        mov edx,dword ptr [esi+14h]
    L_0041c3ea:
        mov ecx,dword ptr [esi+1Ch]
    L_0041c3ed:
        mov dword ptr [esi+10h],edx
    L_0041c3f0:
        fld dword ptr [ecx]
    L_0041c3f2:
        fcomp dword ptr [data_00470b68]
    L_0041c3f8:
        fnstsw ax
    L_0041c3fa:
        test ah,41h
    L_0041c3fd:
        jne short L_0041c420
    L_0041c3ff:
        fld dword ptr [ecx]
    L_0041c401:
        fcomp dword ptr [data_00470b64]
    L_0041c407:
        fnstsw ax
    L_0041c409:
        test ah,5
    L_0041c40c:
        jp short L_0041c420
    L_0041c40e:
        fld dword ptr [esi+18h]
    L_0041c411:
        inc edx
    L_0041c412:
        fadd dword ptr [data_00470afc]
    L_0041c418:
        mov dword ptr [esi+14h],edx
    L_0041c41b:
        fstp dword ptr [esi+18h]
    L_0041c41e:
        jmp short L_0041c430
    L_0041c420:
        fld dword ptr [ecx]
    L_0041c422:
        fadd dword ptr [esi+18h]
    L_0041c425:
        fst dword ptr [esi+18h]
    L_0041c428:
        call asm_FUN_00463b2c_00463b2c
    L_0041c42d:
        mov dword ptr [esi+14h],eax
    L_0041c430:
        test ebx,ebx
    L_0041c432:
        mov esi,ebx
    L_0041c434:
        jne asm_target_0041c340
    L_0041c43a:
        pop ebx
    L_0041c43b:
        mov eax,1
    L_0041c440:
        pop esi
    L_0041c441:
        ret
    }
}
