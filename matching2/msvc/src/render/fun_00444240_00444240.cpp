#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403090..0x0040384F: FUN_00403090
// Naked body preserves the retail register/stack ABI.

// 0x00444240..0x00444571: FUN_00444240
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444240_00444240() {
    __asm {
    L_00444240:
        sub esp,0B0h
    L_00444246:
        push ebx
    L_00444247:
        mov ebx,eax
    L_00444249:
        mov eax,dword ptr [ebx+35Ch]
    L_0044424f:
        test ah,40h
    L_00444252:
        push esi
    L_00444253:
        push edi
    L_00444254:
        jne asm_target_00444337
    L_0044425a:
        test al,0Ch
    L_0044425c:
        je asm_target_00444337
    L_00444262:
        fld dword ptr [ebx+3Ch]
    L_00444265:
        push ebp
    L_00444266:
        lea ebp,[ebx+27Ch]
    L_0044426c:
        lea esi,[ebx+23Ch]
    L_00444272:
        mov ecx,10h
    L_00444277:
        mov edi,ebp
    L_00444279:
        rep movsd
    L_0044427b:
        fmul dword ptr [ebp]
    L_0044427e:
        fstp dword ptr [ebp]
    L_00444281:
        fld dword ptr [ebx+40h]
    L_00444284:
        fmul dword ptr [ebx+290h]
    L_0044428a:
        fstp dword ptr [ebx+290h]
    L_00444290:
        fld dword ptr [ebx+24h]
    L_00444293:
        fld qword ptr [data_00470b70]
    L_00444299:
        and eax,0FFFFFFF7h
    L_0044429c:
        fucompp
    L_0044429e:
        mov dword ptr [ebx+35Ch],eax
    L_004442a4:
        fnstsw ax
    L_004442a6:
        test ah,44h
    L_004442a9:
        jnp short L_004442cb
    L_004442ab:
        mov eax,dword ptr [ebx+24h]
    L_004442ae:
        push eax
    L_004442af:
        lea ecx,[esp+84h]
    L_004442b6:
        push ecx
    L_004442b7:
        call asm_D3DXMatrixRotationX_004521ac
    L_004442bc:
        lea edx,[esp+80h]
    L_004442c3:
        push edx
    L_004442c4:
        push ebp
    L_004442c5:
        push ebp
    L_004442c6:
        call asm_D3DXMatrixMultiply_004521b2
    L_004442cb:
        fld dword ptr [ebx+28h]
    L_004442ce:
        fld qword ptr [data_00470b70]
    L_004442d4:
        fucompp
    L_004442d6:
        fnstsw ax
    L_004442d8:
        test ah,44h
    L_004442db:
        jnp short L_004442fd
    L_004442dd:
        mov eax,dword ptr [ebx+28h]
    L_004442e0:
        push eax
    L_004442e1:
        lea ecx,[esp+84h]
    L_004442e8:
        push ecx
    L_004442e9:
        call asm_D3DXMatrixRotationY_004521b8
    L_004442ee:
        lea edx,[esp+80h]
    L_004442f5:
        push edx
    L_004442f6:
        push ebp
    L_004442f7:
        push ebp
    L_004442f8:
        call asm_D3DXMatrixMultiply_004521b2
    L_004442fd:
        fld dword ptr [ebx+2Ch]
    L_00444300:
        fld qword ptr [data_00470b70]
    L_00444306:
        fucompp
    L_00444308:
        fnstsw ax
    L_0044430a:
        test ah,44h
    L_0044430d:
        jnp short L_0044432f
    L_0044430f:
        mov eax,dword ptr [ebx+2Ch]
    L_00444312:
        push eax
    L_00444313:
        lea ecx,[esp+84h]
    L_0044431a:
        push ecx
    L_0044431b:
        call asm_D3DXMatrixRotationZ_004521be
    L_00444320:
        lea edx,[esp+80h]
    L_00444327:
        push edx
    L_00444328:
        push ebp
    L_00444329:
        push ebp
    L_0044432a:
        call asm_D3DXMatrixMultiply_004521b2
    L_0044432f:
        and dword ptr [ebx+35Ch],0FFFFFFFBh
    L_00444336:
        pop ebp
    L_00444337:
        fld dword ptr [ebx+34Ch]
    L_0044433d:
        lea esi,[ebx+27Ch]
    L_00444343:
        fadd dword ptr [ebx+340h]
    L_00444349:
        mov ecx,10h
    L_0044434e:
        lea edi,[esp+3Ch]
    L_00444352:
        rep movsd
    L_00444354:
        fadd dword ptr [ebx+334h]
    L_0044435a:
        fadd dword ptr [esp+6Ch]
    L_0044435e:
        fstp dword ptr [esp+6Ch]
    L_00444362:
        fld dword ptr [ebx+350h]
    L_00444368:
        fadd dword ptr [ebx+344h]
    L_0044436e:
        fadd dword ptr [ebx+338h]
    L_00444374:
        fadd dword ptr [esp+70h]
    L_00444378:
        fstp dword ptr [esp+70h]
    L_0044437c:
        fld dword ptr [ebx+354h]
    L_00444382:
        fadd dword ptr [ebx+348h]
    L_00444388:
        fadd dword ptr [ebx+33Ch]
    L_0044438e:
        mov ebx,dword ptr [ebx+35Ch]
    L_00444394:
        mov eax,ebx
    L_00444396:
        shr eax,12h
    L_00444399:
        and eax,3
    L_0044439c:
        fstp dword ptr [esp+74h]
    L_004443a0:
        sub eax,0
    L_004443a3:
        je short L_004443ef
    L_004443a5:
        dec eax
    L_004443a6:
        je short L_004443cd
    L_004443a8:
        dec eax
    L_004443a9:
        jne short L_0044440f
    L_004443ab:
        mov dword ptr [esp+24h],0C3800000h
    L_004443b3:
        mov dword ptr [esp+0Ch],0C3800000h
    L_004443bb:
        mov dword ptr [esp+30h],0
    L_004443c3:
        mov dword ptr [esp+18h],0
    L_004443cb:
        jmp short L_0044440f
    L_004443cd:
        mov dword ptr [esp+24h],0
    L_004443d5:
        mov dword ptr [esp+0Ch],0
    L_004443dd:
        mov dword ptr [esp+30h],43800000h
    L_004443e5:
        mov dword ptr [esp+18h],43800000h
    L_004443ed:
        jmp short L_0044440f
    L_004443ef:
        mov dword ptr [esp+24h],0C3000000h
    L_004443f7:
        mov dword ptr [esp+0Ch],0C3000000h
    L_004443ff:
        mov dword ptr [esp+30h],43000000h
    L_00444407:
        mov dword ptr [esp+18h],43000000h
    L_0044440f:
        shr ebx,14h
    L_00444412:
        and ebx,3
    L_00444415:
        sub ebx,0
    L_00444418:
        je short L_00444464
    L_0044441a:
        dec ebx
    L_0044441b:
        je short L_00444442
    L_0044441d:
        dec ebx
    L_0044441e:
        jne short L_00444484
    L_00444420:
        mov dword ptr [esp+1Ch],0C3800000h
    L_00444428:
        mov dword ptr [esp+10h],0C3800000h
    L_00444430:
        mov dword ptr [esp+34h],0
    L_00444438:
        mov dword ptr [esp+28h],0
    L_00444440:
        jmp short L_00444484
    L_00444442:
        mov dword ptr [esp+1Ch],0
    L_0044444a:
        mov dword ptr [esp+10h],0
    L_00444452:
        mov dword ptr [esp+34h],43800000h
    L_0044445a:
        mov dword ptr [esp+28h],43800000h
    L_00444462:
        jmp short L_00444484
    L_00444464:
        mov dword ptr [esp+1Ch],0C3000000h
    L_0044446c:
        mov dword ptr [esp+10h],0C3000000h
    L_00444474:
        mov dword ptr [esp+34h],43000000h
    L_0044447c:
        mov dword ptr [esp+28h],43000000h
    L_00444484:
        lea eax,[esp+3Ch]
    L_00444488:
        push eax
    L_00444489:
        mov eax,dword ptr [data_00491fac]
    L_0044448e:
        lea ecx,[eax+4Ch]
    L_00444491:
        push ecx
    L_00444492:
        lea edx,[eax+8Ch]
    L_00444498:
        push edx
    L_00444499:
        add eax,0CCh
    L_0044449e:
        push eax
    L_0044449f:
        lea eax,[esp+1Ch]
    L_004444a3:
        push eax
    L_004444a4:
        push 4978C0h
    L_004444a9:
        mov dword ptr [esp+50h],0
    L_004444b1:
        mov dword ptr [esp+44h],0
    L_004444b9:
        mov dword ptr [esp+38h],0
    L_004444c1:
        mov dword ptr [esp+2Ch],0
    L_004444c9:
        call asm_D3DXVec3Project_0045218e
    L_004444ce:
        mov eax,dword ptr [data_00491fac]
    L_004444d3:
        lea ecx,[esp+3Ch]
    L_004444d7:
        push ecx
    L_004444d8:
        lea edx,[eax+4Ch]
    L_004444db:
        push edx
    L_004444dc:
        lea ecx,[eax+8Ch]
    L_004444e2:
        push ecx
    L_004444e3:
        add eax,0CCh
    L_004444e8:
        push eax
    L_004444e9:
        lea edx,[esp+28h]
    L_004444ed:
        push edx
    L_004444ee:
        push 4978DCh
    L_004444f3:
        call asm_D3DXVec3Project_0045218e
    L_004444f8:
        lea eax,[esp+3Ch]
    L_004444fc:
        push eax
    L_004444fd:
        mov eax,dword ptr [data_00491fac]
    L_00444502:
        lea ecx,[eax+4Ch]
    L_00444505:
        push ecx
    L_00444506:
        lea edx,[eax+8Ch]
    L_0044450c:
        push edx
    L_0044450d:
        add eax,0CCh
    L_00444512:
        push eax
    L_00444513:
        lea eax,[esp+34h]
    L_00444517:
        push eax
    L_00444518:
        push 4978F8h
    L_0044451d:
        call asm_D3DXVec3Project_0045218e
    L_00444522:
        mov eax,dword ptr [data_00491fac]
    L_00444527:
        lea ecx,[esp+3Ch]
    L_0044452b:
        push ecx
    L_0044452c:
        lea edx,[eax+4Ch]
    L_0044452f:
        push edx
    L_00444530:
        lea ecx,[eax+8Ch]
    L_00444536:
        push ecx
    L_00444537:
        add eax,0CCh
    L_0044453c:
        push eax
    L_0044453d:
        lea edx,[esp+40h]
    L_00444541:
        push edx
    L_00444542:
        push 497914h
    L_00444547:
        call asm_D3DXVec3Project_0045218e
    L_0044454c:
        mov edi,dword ptr [esp+0C0h]
    L_00444553:
        add edi,3AD0F0h
    L_00444559:
        mov ecx,10h
    L_0044455e:
        lea esi,[esp+3Ch]
    L_00444562:
        rep movsd
    L_00444564:
        pop edi
    L_00444565:
        pop esi
    L_00444566:
        xor eax,eax
    L_00444568:
        pop ebx
    L_00444569:
        add esp,0B0h
    L_0044456f:
        ret 4
    }
}
