#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BA50..0x0041BAF4: Enemy_SweepPendingDropsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_SweepPendingDropsRetail_0041ba50() {
    __asm {
    L_0041ba50:
        push ecx
    L_0041ba51:
        push ebp
    L_0041ba52:
        push edi
    L_0041ba53:
        lea edi,[esi+3C0h]
    L_0041ba59:
        mov ebp,96h
    L_0041ba5e:
        mov edi,edi
    L_0041ba60:
        mov eax,dword ptr [edi+30h]
    L_0041ba63:
        test eax,eax
    L_0041ba65:
        je short L_0041bae2
    L_0041ba67:
        mov eax,dword ptr [edi+34h]
    L_0041ba6a:
        cmp eax,1
    L_0041ba6d:
        je short L_0041ba74
    L_0041ba6f:
        cmp eax,4
    L_0041ba72:
        jne short L_0041bae2
    L_0041ba74:
        cmp eax,1
    L_0041ba77:
        mov dword ptr [edi+30h],0
    L_0041ba7e:
        jne short L_0041ba90
    L_0041ba80:
        push 400CCCCDh
    L_0041ba85:
        push 0BFC90FDBh
    L_0041ba8a:
        push 0FFFFFFFFh
    L_0041ba8c:
        push 9
    L_0041ba8e:
        jmp short L_0041babd
    L_0041ba90:
        cmp eax,4
    L_0041ba93:
        jne short L_0041baa5
    L_0041ba95:
        push 400CCCCDh
    L_0041ba9a:
        push 0BFC90FDBh
    L_0041ba9f:
        push 0FFFFFFFFh
    L_0041baa1:
        push 9
    L_0041baa3:
        jmp short L_0041babd
    L_0041baa5:
        cmp eax,0Ah
    L_0041baa8:
        je short L_0041baaf
    L_0041baaa:
        cmp eax,0Bh
    L_0041baad:
        jne short L_0041bae2
    L_0041baaf:
        push 400CCCCDh
    L_0041bab4:
        push 0BFC90FDBh
    L_0041bab9:
        push 0FFFFFFFFh
    L_0041babb:
        push 5
    L_0041babd:
        mov eax,esi
    L_0041babf:
        mov ecx,edi
    L_0041bac1:
        call asm_FUN_0041bb00_0041bb00
    L_0041bac6:
        mov ecx,dword ptr [data_004776f0]
    L_0041bacc:
        mov edx,dword ptr [ecx+3E0B50h]
    L_0041bad2:
        push 189h
    L_0041bad7:
        lea eax,[esp+0Ch]
    L_0041badb:
        push eax
    L_0041badc:
        push edx
    L_0041badd:
        call asm_PlayerAnimation_Create_00448db0
    L_0041bae2:
        add edi,3F0h
    L_0041bae8:
        dec ebp
    L_0041bae9:
        jne asm_target_0041ba60
    L_0041baef:
        pop edi
    L_0041baf0:
        xor eax,eax
    L_0041baf2:
        pop ebp
    L_0041baf3:
        pop ecx
    L_0041baf4:
        ret
    }
}
