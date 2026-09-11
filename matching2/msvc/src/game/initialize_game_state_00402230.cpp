#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.

// 0x00402230..0x00402439: InitializeGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InitializeGameState_00402230() {
    __asm {
    L_00402230:
        sub esp,0Ch
    L_00402233:
        push ebx
    L_00402234:
        push ebp
    L_00402235:
        mov ebp,dword ptr [esp+18h]
    L_00402239:
        test ebp,ebp
    L_0040223b:
        push edi
    L_0040223c:
        mov ebx,eax
    L_0040223e:
        jne short L_00402248
    L_00402240:
        mov dword ptr [data_004776e8],ebx
    L_00402246:
        jmp short L_0040224e
    L_00402248:
        mov dword ptr [data_004776e4],ebx
    L_0040224e:
        mov eax,dword ptr [data_00474c7c]
    L_00402253:
        push ecx
    L_00402254:
        mov dword ptr [ebx+2A30h],eax
    L_0040225a:
        call asm_FUN_00403850_00403850
    L_0040225f:
        test eax,eax
    L_00402261:
        je short L_00402281
    L_00402263:
        push 46CC70h
    L_00402268:
        mov edi,474F70h
    L_0040226d:
        call asm_TextLog_AppendLine_0044b8e0
    L_00402272:
        add esp,4
    L_00402275:
        pop edi
    L_00402276:
        pop ebp
    L_00402277:
        or eax,0FFFFFFFFh
    L_0040227a:
        pop ebx
    L_0040227b:
        add esp,0Ch
    L_0040227e:
        ret 4
    L_00402281:
        lea eax,[ebx+2A4Ch]
    L_00402287:
        mov edi,eax
    L_00402289:
        push esi
    L_0040228a:
        mov dword ptr [esp+10h],0
    L_00402292:
        mov edx,dword ptr [esp+10h]
    L_00402296:
        mov ecx,46h
    L_0040229b:
        mov esi,491D7Ch
    L_004022a0:
        rep movsd
    L_004022a2:
        mov dword ptr [eax],edx
    L_004022a4:
        mov dword ptr [esp+14h],0
    L_004022ac:
        mov ecx,dword ptr [esp+14h]
    L_004022b0:
        mov dword ptr [eax+4],ecx
    L_004022b3:
        mov dword ptr [esp+18h],0C4160000h
    L_004022bb:
        mov edx,dword ptr [esp+18h]
    L_004022bf:
        mov dword ptr [eax+8],edx
    L_004022c2:
        mov dword ptr [esp+10h],0
    L_004022ca:
        mov ecx,dword ptr [esp+10h]
    L_004022ce:
        lea eax,[ebx+2A58h]
    L_004022d4:
        mov dword ptr [eax],ecx
    L_004022d6:
        mov dword ptr [esp+14h],43960000h
    L_004022de:
        mov edx,dword ptr [esp+14h]
    L_004022e2:
        mov dword ptr [eax+4],edx
    L_004022e5:
        mov dword ptr [esp+18h],44160000h
    L_004022ed:
        mov ecx,dword ptr [esp+18h]
    L_004022f1:
        mov dword ptr [eax+8],ecx
    L_004022f4:
        mov dword ptr [esp+10h],0
    L_004022fc:
        mov eax,dword ptr [esp+10h]
    L_00402300:
        lea edx,[ebx+2A64h]
    L_00402306:
        mov dword ptr [edx],eax
    L_00402308:
        mov dword ptr [esp+14h],3F800000h
    L_00402310:
        mov ecx,dword ptr [esp+14h]
    L_00402314:
        mov dword ptr [edx+4],ecx
    L_00402317:
        mov dword ptr [esp+18h],0
    L_0040231f:
        mov eax,dword ptr [esp+18h]
    L_00402323:
        mov dword ptr [edx+8],eax
    L_00402326:
        mov dword ptr [esp+10h],0
    L_0040232e:
        mov edx,dword ptr [esp+10h]
    L_00402332:
        lea ecx,[ebx+2A88h]
    L_00402338:
        mov dword ptr [ecx],edx
    L_0040233a:
        mov dword ptr [esp+14h],0
    L_00402342:
        mov eax,dword ptr [esp+14h]
    L_00402346:
        mov dword ptr [esp+18h],0
    L_0040234e:
        mov edx,dword ptr [esp+18h]
    L_00402352:
        mov dword ptr [ecx+4],eax
    L_00402355:
        push 403050h
    L_0040235a:
        mov dword ptr [ecx+8],edx
    L_0040235d:
        mov dword ptr [ebx+1EE0h],4B12A310h
    L_00402367:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040236c:
        mov esi,eax
    L_0040236e:
        mov edx,dword ptr [esi+4]
    L_00402371:
        mov eax,dword ptr [data_00491be4]
    L_00402376:
        and edx,0FFFFFFFDh
    L_00402379:
        lea edi,[ebp+0Ch]
    L_0040237c:
        push eax
    L_0040237d:
        mov dword ptr [esi+20h],ebx
    L_00402380:
        mov dword ptr [esi+4],edx
    L_00402383:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00402388:
        push 403060h
    L_0040238d:
        mov dword ptr [ebx+8],esi
    L_00402390:
        call asm_SchedulerCallback_Create_00449ed0
    L_00402395:
        mov ecx,dword ptr [data_00491be4]
    L_0040239b:
        mov esi,eax
    L_0040239d:
        and dword ptr [esi+4],0FFFFFFFDh
    L_004023a1:
        lea edi,[ebp+7]
    L_004023a4:
        push ecx
    L_004023a5:
        mov dword ptr [esi+20h],ebx
    L_004023a8:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004023ad:
        push 403070h
    L_004023b2:
        mov dword ptr [ebx+0Ch],esi
    L_004023b5:
        call asm_SchedulerCallback_Create_00449ed0
    L_004023ba:
        mov edx,dword ptr [data_00491be4]
    L_004023c0:
        mov esi,eax
    L_004023c2:
        mov eax,dword ptr [esi+4]
    L_004023c5:
        and eax,0FFFFFFFDh
    L_004023c8:
        lea edi,[ebp+0Ah]
    L_004023cb:
        push edx
    L_004023cc:
        mov dword ptr [esi+20h],ebx
    L_004023cf:
        mov dword ptr [esi+4],eax
    L_004023d2:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004023d7:
        xor ecx,ecx
    L_004023d9:
        mov dword ptr [ebx+2A40h],esi
    L_004023df:
        mov dword ptr [ebx+2A34h],ecx
    L_004023e5:
        mov eax,dword ptr [ebx+48h]
    L_004023e8:
        test al,1
    L_004023ea:
        pop esi
    L_004023eb:
        jne short L_00402407
    L_004023ed:
        or eax,1
    L_004023f0:
        mov dword ptr [ebx+3Ch],ecx
    L_004023f3:
        mov dword ptr [ebx+38h],0FFF0BDC1h
    L_004023fa:
        mov dword ptr [ebx+40h],ecx
    L_004023fd:
        mov dword ptr [ebx+44h],476F78h
    L_00402404:
        mov dword ptr [ebx+48h],eax
    L_00402407:
        mov dword ptr [ebx+3Ch],ecx
    L_0040240a:
        mov dword ptr [ebx+40h],ecx
    L_0040240d:
        mov dword ptr [ebx+38h],0FFFFFFFFh
    L_00402414:
        mov eax,dword ptr [ebx+2A18h]
    L_0040241a:
        pop edi
    L_0040241b:
        or eax,1
    L_0040241e:
        mov dword ptr [ebx+2A18h],eax
    L_00402424:
        pop ebp
    L_00402425:
        mov dword ptr [ebx+94h],ecx
    L_0040242b:
        mov dword ptr [ebx+0E0h],ecx
    L_00402431:
        xor eax,eax
    L_00402433:
        pop ebx
    L_00402434:
        add esp,0Ch
    L_00402437:
        ret 4
    }
}
