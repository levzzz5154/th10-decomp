#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D300..0x0042D40B: FUN_0042d300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d300_0042d300() {
    __asm {
    L_0042d300:
        push ecx
    L_0042d301:
        mov eax,dword ptr [ebx+20h]
    L_0042d304:
        cmp eax,4
    L_0042d307:
        ja asm_target_0042d405
    L_0042d30d:
        push edi
    L_0042d30e:
        jmp dword ptr [eax*4+42D40Ch]
    L_0042d315:
        mov eax,dword ptr [ebx+424h]
    L_0042d31b:
        mov edx,dword ptr [data_00491c10]
    L_0042d321:
        push eax
    L_0042d322:
        call asm_AnimationManager_Find_004491c0
    L_0042d327:
        test eax,eax
    L_0042d329:
        jne short L_0042d35a
    L_0042d32b:
        push ebx
    L_0042d32c:
        mov edi,58h
    L_0042d331:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d336:
        push ebx
    L_0042d337:
        mov edi,5Ah
    L_0042d33c:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d341:
        mov ecx,dword ptr [ebx+18h]
    L_0042d344:
        push 0Fh
    L_0042d346:
        push 0
    L_0042d348:
        push ecx
    L_0042d349:
        lea edi,[esp+10h]
    L_0042d34d:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0042d352:
        mov edx,dword ptr [eax]
    L_0042d354:
        mov dword ptr [ebx+684h],edx
    L_0042d35a:
        mov ecx,1
    L_0042d35f:
        mov eax,ebx
    L_0042d361:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d366:
        mov eax,dword ptr [ebx+2Ch]
    L_0042d369:
        test eax,eax
    L_0042d36b:
        je short L_0042d37c
    L_0042d36d:
        jg short L_0042d375
    L_0042d36f:
        dec eax
    L_0042d370:
        mov dword ptr [ebx+24h],eax
    L_0042d373:
        jmp short L_0042d383
    L_0042d375:
        xor eax,eax
    L_0042d377:
        mov dword ptr [ebx+24h],eax
    L_0042d37a:
        jmp short L_0042d383
    L_0042d37c:
        mov dword ptr [ebx+24h],0
    L_0042d383:
        cmp dword ptr [ebx+2B4h],0Ah
    L_0042d38a:
        jle short L_0042d404
    L_0042d38c:
        mov ecx,2
    L_0042d391:
        mov eax,ebx
    L_0042d393:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d398:
        pop edi
    L_0042d399:
        mov eax,1
    L_0042d39e:
        pop ecx
    L_0042d39f:
        ret
    L_0042d3a0:
        test dword ptr [data_00474e36],160Bh
    L_0042d3aa:
        je short L_0042d404
    L_0042d3ac:
        push esi
    L_0042d3ad:
        mov esi,6
    L_0042d3b2:
        mov ecx,5Ah
    L_0042d3b7:
        mov eax,ebx
    L_0042d3b9:
        call asm_FUN_0042c770_0042c770
    L_0042d3be:
        mov ecx,4
    L_0042d3c3:
        mov eax,ebx
    L_0042d3c5:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d3ca:
        push 0
    L_0042d3cc:
        mov edi,20h
    L_0042d3d1:
        mov ecx,492590h
    L_0042d3d6:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d3db:
        lea eax,[ebx+684h]
    L_0042d3e1:
        call asm_FUN_00409e50_00409e50
    L_0042d3e6:
        pop esi
    L_0042d3e7:
        pop edi
    L_0042d3e8:
        mov eax,1
    L_0042d3ed:
        pop ecx
    L_0042d3ee:
        ret
    L_0042d3ef:
        cmp dword ptr [ebx+2B4h],1Eh
    L_0042d3f6:
        jl short L_0042d404
    L_0042d3f8:
        mov ecx,2
    L_0042d3fd:
        mov eax,ebx
    L_0042d3ff:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d404:
        pop edi
    L_0042d405:
        mov eax,1
    L_0042d40a:
        pop ecx
    L_0042d40b:
        ret
    }
}
