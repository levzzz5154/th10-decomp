// BLOCKED (D3802): closest_byte_count=95/95; first_diff=0x0040D6B0;
// residual_class=private register ABI: retail homes the manager in EBX for
// 0x0040D280 and passes it in EAX to 0x0040D530, while a standalone readable
// declaration homes it in ESI and passes it through ECX.
// variants_tested=live Ghidra decompile with callers 0x0040A350 and
// 0x00417B33; MSVC 13.10 standalone schema-1 candidate (95 bytes, 9
// differing register bytes); merged native-LTCG scratch cluster with
// 0x0040D280/0x0040D530 (95/95 exact, not landable because 0x0040D530
// retained four argument-copy mismatches).
// next_lever=promote 0x0040D530 and its EAX-receiver callers together with
// this factory and 0x0040D280 in one real-caller schema-2/native-LTCG link;
// do not replace the exact assembly until the complete cluster is exact.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0040D6B0..0x0040D70E: EnemyManager_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EnemyManager_CreateRetail_0040d6b0() {
    __asm {
    L_0040d6b0:
        push ebx
    L_0040d6b1:
        push 68h
    L_0040d6b3:
        call asm_operator_new_00452493
    L_0040d6b8:
        mov edx,eax
    L_0040d6ba:
        add esp,4
    L_0040d6bd:
        test edx,edx
    L_0040d6bf:
        je short L_0040d6df
    L_0040d6c1:
        and dword ptr [edx+50h],0FFFFFFFEh
    L_0040d6c5:
        push edi
    L_0040d6c6:
        xor eax,eax
    L_0040d6c8:
        mov ecx,1Ah
    L_0040d6cd:
        mov edi,edx
    L_0040d6cf:
        rep stosd
    L_0040d6d1:
        or dword ptr [edx],2
    L_0040d6d4:
        mov dword ptr [data_00477704],edx
    L_0040d6da:
        mov ebx,edx
    L_0040d6dc:
        pop edi
    L_0040d6dd:
        jmp short L_0040d6e1
    L_0040d6df:
        xor ebx,ebx
    L_0040d6e1:
        mov eax,dword ptr [esp+8]
    L_0040d6e5:
        push eax
    L_0040d6e6:
        call asm_FUN_0040d280_0040d280
    L_0040d6eb:
        test eax,eax
    L_0040d6ed:
        je short L_0040d709
    L_0040d6ef:
        test ebx,ebx
    L_0040d6f1:
        je short L_0040d703
    L_0040d6f3:
        mov eax,ebx
    L_0040d6f5:
        call asm_FUN_0040d530_0040d530
    L_0040d6fa:
        push ebx
    L_0040d6fb:
        call asm_free_004524a1
    L_0040d700:
        add esp,4
    L_0040d703:
        xor eax,eax
    L_0040d705:
        pop ebx
    L_0040d706:
        ret 4
    L_0040d709:
        mov eax,ebx
    L_0040d70b:
        pop ebx
    L_0040d70c:
        ret 4
    }
}
