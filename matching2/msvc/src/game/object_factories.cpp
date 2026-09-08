#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C290..0x0041C2EA: ScoreManager_CreateAndInitRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreManager_CreateAndInitRetail_0041c290() {
    __asm {
    L_0041c290:
        push esi
    L_0041c291:
        push 45Ch
    L_0041c296:
        call asm_operator_new_00452493
    L_0041c29b:
        mov esi,eax
    L_0041c29d:
        add esp,4
    L_0041c2a0:
        test esi,esi
    L_0041c2a2:
        je short L_0041c2c1
    L_0041c2a4:
        push edi
    L_0041c2a5:
        lea edx,[esi+10h]
    L_0041c2a8:
        call asm_ScoreObject_Initialize_0041c030
    L_0041c2ad:
        mov ecx,117h
    L_0041c2b2:
        xor eax,eax
    L_0041c2b4:
        mov edi,esi
    L_0041c2b6:
        rep stosd
    L_0041c2b8:
        mov dword ptr [data_0047781c],esi
    L_0041c2be:
        pop edi
    L_0041c2bf:
        jmp short L_0041c2c3
    L_0041c2c1:
        xor esi,esi
    L_0041c2c3:
        push ebx
    L_0041c2c4:
        mov ebx,esi
    L_0041c2c6:
        call asm_ScoreDisplay_RegisterTasksRetail_0041c120
    L_0041c2cb:
        test eax,eax
    L_0041c2cd:
        pop ebx
    L_0041c2ce:
        je short L_0041c2e7
    L_0041c2d0:
        test esi,esi
    L_0041c2d2:
        je short L_0041c2e3
    L_0041c2d4:
        push esi
    L_0041c2d5:
        call asm_ScoreExtendedObject_DestroyRetail_0041c1c0
    L_0041c2da:
        push esi
    L_0041c2db:
        call asm_free_004524a1
    L_0041c2e0:
        add esp,4
    L_0041c2e3:
        xor eax,eax
    L_0041c2e5:
        pop esi
    L_0041c2e6:
        ret
    L_0041c2e7:
        mov eax,esi
    L_0041c2e9:
        pop esi
    L_0041c2ea:
        ret
    }
}

// 0x0041FD00..0x0041FD44: EnemySlot_CreateAndInitRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EnemySlot_CreateAndInitRetail_0041fd00() {
    __asm {
    L_0041fd00:
        push ebx
    L_0041fd01:
        push 3F0h
    L_0041fd06:
        call asm_operator_new_00452493
    L_0041fd0b:
        add esp,4
    L_0041fd0e:
        test eax,eax
    L_0041fd10:
        je short L_0041fd1f
    L_0041fd12:
        push esi
    L_0041fd13:
        mov esi,eax
    L_0041fd15:
        call asm_Recovery_InitializeStateTable_0041f850
    L_0041fd1a:
        mov ebx,eax
    L_0041fd1c:
        pop esi
    L_0041fd1d:
        jmp short L_0041fd21
    L_0041fd1f:
        xor ebx,ebx
    L_0041fd21:
        call asm_Recovery_StartWorker_0041fac0
    L_0041fd26:
        test eax,eax
    L_0041fd28:
        je short L_0041fd41
    L_0041fd2a:
        test ebx,ebx
    L_0041fd2c:
        je short L_0041fd3d
    L_0041fd2e:
        push ebx
    L_0041fd2f:
        call asm_FUN_0041fb50_0041fb50
    L_0041fd34:
        push ebx
    L_0041fd35:
        call asm_free_004524a1
    L_0041fd3a:
        add esp,4
    L_0041fd3d:
        xor eax,eax
    L_0041fd3f:
        pop ebx
    L_0041fd40:
        ret
    L_0041fd41:
        mov eax,ebx
    L_0041fd43:
        pop ebx
    L_0041fd44:
        ret
    }
}
