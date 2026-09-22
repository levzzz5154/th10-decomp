// BLOCKED (D3801): closest_byte_count=0/151; first_diff=none (exact retail
// naked baseline; no readable candidate retained).
// residual_class=compiler-generated SEH registration/handler frame, stdcall
// ret-8 ABI, and the Construct/Initialize/DestroyGameState constructor
// cluster called by 0x00417A9E and 0x00417B17.
// variants_tested=live Ghidra decompilation with callers 0x00417A9E/
// 0x00417B17 and callee topology; readable operator-new/vector-constructor
// candidate (MSVC 13.10 C2733/C2664 in the paired ConstructGameState
// declaration); exact naked baseline probe=151/151.
// next_lever=typed native-LTCG Create/Construct/Initialize/Destroy cluster
// with the production stdcall declaration and EH helper ABI.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.
// 0x00402640..0x004026D6: CreateGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CreateGameState_00402640() {
    __asm {
    L_00402640:
        push 0FFFFFFFFh
    L_00402642:
        push 46588Bh
    L_00402647:
        mov eax,dword ptr fs:[0]
    L_0040264d:
        push eax
    L_0040264e:
        mov dword ptr fs:[0],esp
    L_00402655:
        push ecx
    L_00402656:
        push esi
    L_00402657:
        push 2B64h
    L_0040265c:
        call asm_operator_new_00452493
    L_00402661:
        add esp,4
    L_00402664:
        mov dword ptr [esp+4],eax
    L_00402668:
        test eax,eax
    L_0040266a:
        mov dword ptr [esp+10h],0
    L_00402672:
        je short L_0040267e
    L_00402674:
        push eax
    L_00402675:
        call asm_ConstructGameState_00402160
    L_0040267a:
        mov esi,eax
    L_0040267c:
        jmp short L_00402680
    L_0040267e:
        xor esi,esi
    L_00402680:
        mov eax,dword ptr [esp+1Ch]
    L_00402684:
        mov ecx,dword ptr [esp+18h]
    L_00402688:
        push eax
    L_00402689:
        mov eax,esi
    L_0040268b:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_00402693:
        call asm_InitializeGameState_00402230
    L_00402698:
        test eax,eax
    L_0040269a:
        je short L_004026c3
    L_0040269c:
        test esi,esi
    L_0040269e:
        je short L_004026af
    L_004026a0:
        push esi
    L_004026a1:
        call asm_DestroyGameState_00402440
    L_004026a6:
        push esi
    L_004026a7:
        call asm_free_004524a1
    L_004026ac:
        add esp,4
    L_004026af:
        xor eax,eax
    L_004026b1:
        pop esi
    L_004026b2:
        mov ecx,dword ptr [esp+4]
    L_004026b6:
        mov dword ptr fs:[0],ecx
    L_004026bd:
        add esp,10h
    L_004026c0:
        ret 8
    L_004026c3:
        mov ecx,dword ptr [esp+8]
    L_004026c7:
        mov eax,esi
    L_004026c9:
        pop esi
    L_004026ca:
        mov dword ptr fs:[0],ecx
    L_004026d1:
        add esp,10h
    L_004026d4:
        ret 8
    }
}
