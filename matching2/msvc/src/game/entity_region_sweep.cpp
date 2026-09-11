#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408210..0x004082D2: FUN_00408210
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408210_00408210() {
    __asm {
    L_00408210:
        sub esp,3Ch
    L_00408213:
        fld dword ptr [ebx+50h]
    L_00408216:
        push esi
    L_00408217:
        fmul dword ptr [data_00470b0c]
    L_0040821d:
        push edi
    L_0040821e:
        lea esi,[ebx+60h]
    L_00408221:
        mov dword ptr [esp+0Ch],7D0h
    L_00408229:
        fstp dword ptr [esp+20h]
    L_0040822d:
        mov eax,dword ptr [esp+20h]
    L_00408231:
        fld dword ptr [ebx+54h]
    L_00408234:
        mov dword ptr [esp+14h],eax
    L_00408238:
        fmul dword ptr [data_00470b0c]
    L_0040823e:
        fstp dword ptr [esp+24h]
    L_00408242:
        mov ecx,dword ptr [esp+24h]
    L_00408246:
        fld dword ptr [ebx+58h]
    L_00408249:
        mov dword ptr [esp+18h],ecx
    L_0040824d:
        fmul dword ptr [data_00470b0c]
    L_00408253:
        fstp dword ptr [esp+28h]
    L_00408257:
        mov edx,dword ptr [esp+28h]
    L_0040825b:
        fld dword ptr [ebx+44h]
    L_0040825e:
        mov dword ptr [esp+1Ch],edx
    L_00408262:
        fsub dword ptr [esp+14h]
    L_00408266:
        fstp dword ptr [esp+20h]
    L_0040826a:
        mov eax,dword ptr [esp+20h]
    L_0040826e:
        fld dword ptr [ebx+48h]
    L_00408271:
        mov dword ptr [esp+2Ch],eax
    L_00408275:
        fsub dword ptr [esp+18h]
    L_00408279:
        fstp dword ptr [esp+24h]
    L_0040827d:
        mov ecx,dword ptr [esp+24h]
    L_00408281:
        fld dword ptr [ebx+4Ch]
    L_00408284:
        mov dword ptr [esp+30h],ecx
    L_00408288:
        fsub dword ptr [esp+1Ch]
    L_0040828c:
        fstp dword ptr [esp+28h]
    L_00408290:
        mov edx,dword ptr [esp+28h]
    L_00408294:
        fld dword ptr [esp+14h]
    L_00408298:
        mov dword ptr [esp+34h],edx
    L_0040829c:
        fadd dword ptr [ebx+44h]
    L_0040829f:
        fstp dword ptr [esp+20h]
    L_004082a3:
        mov eax,dword ptr [esp+20h]
    L_004082a7:
        fld dword ptr [esp+18h]
    L_004082ab:
        mov dword ptr [esp+14h],eax
    L_004082af:
        fadd dword ptr [ebx+48h]
    L_004082b2:
        fstp dword ptr [esp+24h]
    L_004082b6:
        mov ecx,dword ptr [esp+24h]
    L_004082ba:
        fld dword ptr [esp+1Ch]
    L_004082be:
        mov dword ptr [esp+18h],ecx
    L_004082c2:
        fadd dword ptr [ebx+4Ch]
    L_004082c5:
        fstp dword ptr [esp+28h]
    L_004082c9:
        mov edx,dword ptr [esp+28h]
    L_004082cd:
        mov dword ptr [esp+1Ch],edx
    L_004082d1:
        TH10_REL8(0xeb, 0x004082d1, VA_asm_FUN_00408210_part_004082e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004082e0:
        mov ax,word ptr [esi+446h]
    L_004082e7:
        test ax,ax
    L_004082ea:
        je asm_target_0040843a
    L_004082f0:
        cmp ax,3
    L_004082f4:
        je asm_target_0040843a
    L_004082fa:
        fld dword ptr [esi+3F0h]
    L_00408300:
        lea edi,[esi+3B4h]
    L_00408306:
        fmul dword ptr [data_00470b0c]
    L_0040830c:
        fld dword ptr [edi]
    L_0040830e:
        fsub st,st(1)
    L_00408310:
        fstp dword ptr [esp+20h]
    L_00408314:
        fld dword ptr [esi+3F4h]
    L_0040831a:
        fmul dword ptr [data_00470b0c]
    L_00408320:
        fstp dword ptr [esp+8]
    L_00408324:
        fld dword ptr [esi+3B8h]
    L_0040832a:
        fsub dword ptr [esp+8]
    L_0040832e:
        fstp dword ptr [esp+24h]
    L_00408332:
        fadd dword ptr [edi]
    L_00408334:
        fld dword ptr [esp+8]
    L_00408338:
        fadd dword ptr [esi+3B8h]
    L_0040833e:
        fstp dword ptr [esp+3Ch]
    L_00408342:
        fcomp dword ptr [esp+2Ch]
    L_00408346:
        fnstsw ax
    L_00408348:
        test ah,5
    L_0040834b:
        jnp asm_target_0040843a
    L_00408351:
        fld dword ptr [esp+20h]
    L_00408355:
        fcomp dword ptr [esp+14h]
    L_00408359:
        fnstsw ax
    L_0040835b:
        test ah,41h
    L_0040835e:
        je asm_target_0040843a
    L_00408364:
        fld dword ptr [esp+3Ch]
    L_00408368:
        fcomp dword ptr [esp+30h]
    L_0040836c:
        fnstsw ax
    L_0040836e:
        test ah,5
    L_00408371:
        jnp asm_target_0040843a
    L_00408377:
        fld dword ptr [esp+24h]
    L_0040837b:
        fcomp dword ptr [esp+18h]
    L_0040837f:
        fnstsw ax
    L_00408381:
        test ah,41h
    L_00408384:
        je asm_target_0040843a
    L_0040838a:
        mov ecx,dword ptr [esi]
    L_0040838c:
        mov eax,dword ptr [esp+48h]
    L_00408390:
        or ecx,8
    L_00408393:
        test eax,eax
    L_00408395:
        mov dword ptr [esi],ecx
    L_00408397:
        je short L_004083b3
    L_00408399:
        mov eax,dword ptr [data_00477818]
    L_0040839e:
        push 3F19999Ah
    L_004083a3:
        push 0BFC90FDBh
    L_004083a8:
        push 0FFFFFFFFh
    L_004083aa:
        push 8
    L_004083ac:
        mov ecx,edi
    L_004083ae:
        call asm_FUN_0041bb00_0041bb00
    L_004083b3:
        mov ecx,dword ptr [ebx+3E0B50h]
    L_004083b9:
        push 173h
    L_004083be:
        lea eax,[esp+14h]
    L_004083c2:
        push eax
    L_004083c3:
        push ecx
    L_004083c4:
        call asm_PlayerAnimation_Create_00448db0
    L_004083c9:
        mov edx,dword ptr [eax]
    L_004083cb:
        push edx
    L_004083cc:
        mov edx,dword ptr [data_00491c10]
    L_004083d2:
        call asm_AnimationManager_Find_004491c0
    L_004083d7:
        mov ecx,dword ptr [esi+39Ch]
    L_004083dd:
        test ecx,ecx
    L_004083df:
        mov edx,eax
    L_004083e1:
        je short L_00408430
    L_004083e3:
        fld dword ptr [ecx+34h]
    L_004083e6:
        fcomp dword ptr [data_00470b48]
    L_004083ec:
        fnstsw ax
    L_004083ee:
        test ah,41h
    L_004083f1:
        jp short L_00408403
    L_004083f3:
        movsx eax,word ptr [esi+7ECh]
    L_004083fa:
        mov ecx,dword ptr [eax*4+474350h]
    L_00408401:
        jmp short L_0040842a
    L_00408403:
        fld dword ptr [ecx+34h]
    L_00408406:
        fcomp dword ptr [data_00470bcc]
    L_0040840c:
        fnstsw ax
    L_0040840e:
        test ah,41h
    L_00408411:
        movsx eax,word ptr [esi+7ECh]
    L_00408418:
        jp short L_00408423
    L_0040841a:
        mov ecx,dword ptr [eax*4+474390h]
    L_00408421:
        jmp short L_0040842a
    L_00408423:
        mov ecx,dword ptr [eax*4+4743B0h]
    L_0040842a:
        mov dword ptr [edx+2FCh],ecx
    L_00408430:
        mov dword ptr [esi+450h],0
    L_0040843a:
        mov eax,dword ptr [esp+0Ch]
    L_0040843e:
        add esi,7F0h
    L_00408444:
        dec eax
    L_00408445:
        mov dword ptr [esp+0Ch],eax
    L_00408449:
        jne asm_FUN_00408210_part_004082e0
    L_0040844f:
        pop edi
    L_00408450:
        xor eax,eax
    L_00408452:
        pop esi
    L_00408453:
        add esp,3Ch
    L_00408456:
        ret 4
    }
}
