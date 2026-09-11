#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C290..0x0041C2EA: ScoreManager_CreateAndInitRetail
// Naked body preserves the retail register/stack ABI.

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
