#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D280..0x0040D3CD: FUN_0040d280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d280_0040d280() {
    __asm {
    L_0040d280:
        mov eax,dword ptr [data_004776f0]
    L_0040d285:
        mov ecx,dword ptr [eax+3E0B50h]
    L_0040d28b:
        push ebp
    L_0040d28c:
        push edi
    L_0040d28d:
        push 1098h
    L_0040d292:
        mov dword ptr [ebx+30h],ecx
    L_0040d295:
        call asm_operator_new_00452493
    L_0040d29a:
        mov edx,eax
    L_0040d29c:
        xor ebp,ebp
    L_0040d29e:
        add esp,4
    L_0040d2a1:
        cmp edx,ebp
    L_0040d2a3:
        je short L_0040d2c6
    L_0040d2a5:
        mov dword ptr [edx+1090h],ebp
    L_0040d2ab:
        mov dword ptr [edx+1094h],ebp
    L_0040d2b1:
        mov ecx,426h
    L_0040d2b6:
        xor eax,eax
    L_0040d2b8:
        mov edi,edx
    L_0040d2ba:
        rep stosd
    L_0040d2bc:
        mov dword ptr [edx],46D0B4h
    L_0040d2c2:
        mov ecx,edx
    L_0040d2c4:
        jmp short L_0040d2c8
    L_0040d2c6:
        xor ecx,ecx
    L_0040d2c8:
        mov eax,dword ptr [esp+0Ch]
    L_0040d2cc:
        push esi
    L_0040d2cd:
        mov dword ptr [ebx+54h],ecx
    L_0040d2d0:
        mov edx,dword ptr [ecx]
    L_0040d2d2:
        push eax
    L_0040d2d3:
        call dword ptr [edx+8]
    L_0040d2d6:
        push 24h
    L_0040d2d8:
        call asm_operator_new_00452493
    L_0040d2dd:
        add esp,4
    L_0040d2e0:
        cmp eax,ebp
    L_0040d2e2:
        je short L_0040d305
    L_0040d2e4:
        mov ecx,dword ptr [eax+4]
    L_0040d2e7:
        mov dword ptr [eax+8],ebp
    L_0040d2ea:
        mov dword ptr [eax+0Ch],ebp
    L_0040d2ed:
        mov dword ptr [eax+10h],ebp
    L_0040d2f0:
        mov dword ptr [eax],ebp
    L_0040d2f2:
        and ecx,0FFFFFFFEh
    L_0040d2f5:
        mov dword ptr [eax+4],ecx
    L_0040d2f8:
        mov dword ptr [eax+14h],eax
    L_0040d2fb:
        mov dword ptr [eax+18h],ebp
    L_0040d2fe:
        mov dword ptr [eax+1Ch],ebp
    L_0040d301:
        mov esi,eax
    L_0040d303:
        jmp short L_0040d307
    L_0040d305:
        xor esi,esi
    L_0040d307:
        mov ecx,dword ptr [esi+4]
    L_0040d30a:
        mov edx,dword ptr [data_00491be4]
    L_0040d310:
        and ecx,0FFFFFFFDh
    L_0040d313:
        or ecx,1
    L_0040d316:
        push edx
    L_0040d317:
        mov edi,12h
    L_0040d31c:
        mov dword ptr [esi+8],40D810h
    L_0040d323:
        mov dword ptr [esi+0Ch],ebp
    L_0040d326:
        mov dword ptr [esi+10h],ebp
    L_0040d329:
        mov dword ptr [esi+20h],ebx
    L_0040d32c:
        mov dword ptr [esi+4],ecx
    L_0040d32f:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0040d334:
        push 24h
    L_0040d336:
        mov dword ptr [ebx+8],esi
    L_0040d339:
        call asm_operator_new_00452493
    L_0040d33e:
        add esp,4
    L_0040d341:
        cmp eax,ebp
    L_0040d343:
        je short L_0040d366
    L_0040d345:
        mov ecx,dword ptr [eax+4]
    L_0040d348:
        mov dword ptr [eax+8],ebp
    L_0040d34b:
        mov dword ptr [eax+0Ch],ebp
    L_0040d34e:
        mov dword ptr [eax+10h],ebp
    L_0040d351:
        mov dword ptr [eax],ebp
    L_0040d353:
        and ecx,0FFFFFFFEh
    L_0040d356:
        mov dword ptr [eax+4],ecx
    L_0040d359:
        mov dword ptr [eax+14h],eax
    L_0040d35c:
        mov dword ptr [eax+18h],ebp
    L_0040d35f:
        mov dword ptr [eax+1Ch],ebp
    L_0040d362:
        mov esi,eax
    L_0040d364:
        jmp short L_0040d368
    L_0040d366:
        xor esi,esi
    L_0040d368:
        mov eax,dword ptr [esi+4]
    L_0040d36b:
        mov ecx,dword ptr [data_00491be4]
    L_0040d371:
        and eax,0FFFFFFFDh
    L_0040d374:
        or eax,1
    L_0040d377:
        push ecx
    L_0040d378:
        mov edi,14h
    L_0040d37d:
        mov dword ptr [esi+8],40D820h
    L_0040d384:
        mov dword ptr [esi+0Ch],ebp
    L_0040d387:
        mov dword ptr [esi+10h],ebp
    L_0040d38a:
        mov dword ptr [esi+20h],ebx
    L_0040d38d:
        mov dword ptr [esi+4],eax
    L_0040d390:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040d395:
        mov dword ptr [ebx+0Ch],esi
    L_0040d398:
        mov eax,dword ptr [ebx+50h]
    L_0040d39b:
        test al,1
    L_0040d39d:
        pop esi
    L_0040d39e:
        jne short L_0040d3ba
    L_0040d3a0:
        or eax,1
    L_0040d3a3:
        mov dword ptr [ebx+44h],ebp
    L_0040d3a6:
        mov dword ptr [ebx+40h],0FFF0BDC1h
    L_0040d3ad:
        mov dword ptr [ebx+48h],ebp
    L_0040d3b0:
        mov dword ptr [ebx+4Ch],476F78h
    L_0040d3b7:
        mov dword ptr [ebx+50h],eax
    L_0040d3ba:
        pop edi
    L_0040d3bb:
        mov dword ptr [ebx+44h],ebp
    L_0040d3be:
        mov dword ptr [ebx+48h],ebp
    L_0040d3c1:
        mov dword ptr [ebx+40h],0FFFFFFFFh
    L_0040d3c8:
        xor eax,eax
    L_0040d3ca:
        pop ebp
    L_0040d3cb:
        ret 4
    }
}
