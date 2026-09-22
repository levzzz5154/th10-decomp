// BLOCKED (D3803): closest_byte_count=0/96; first_diff=0x0042CD50
// (no readable native-LTCG body retained).
// residual_class=private worker receiver/field layout, the 0x0042C920
// constructor's EDX receiver convention, the 0x0044C150 stop-worker call,
// and the six-argument __beginthreadex ABI with the callback at 0x0042C9F0.
// variants_tested=live Ghidra complete decompile with caller 0x00421986 and
// callees 0x00452493/0x0042C920/0x0044C150/0x00453683; MSVC 13.10.6030
// authoritative production probe (96/96 exact); native-LTCG cluster
// feasibility review using the real caller and constructor/stop-worker
// dependency topology.
// next_lever=compile a schema-2 native-LTCG cluster with 0x00421986,
// 0x0042C920 and 0x0044C150 visible, plus the beginthreadex import binding,
// then measure the complete body before changing production metadata.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042CD50..0x0042CDAF: ?ProgressManager_CreateAndStartWorker@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ProgressManager_CreateAndStartWorker_0042cd50() {
    __asm {
    L_0042cd50:
        push esi
    L_0042cd51:
        push edi
    L_0042cd52:
        push 5ACCh
    L_0042cd57:
        call asm_operator_new_00452493
    L_0042cd5c:
        add esp,4
    L_0042cd5f:
        test eax,eax
    L_0042cd61:
        je short L_0042cd6e
    L_0042cd63:
        mov edx,eax
    L_0042cd65:
        call asm_FUN_0042c920_0042c920
    L_0042cd6a:
        mov edi,eax
    L_0042cd6c:
        jmp short L_0042cd70
    L_0042cd6e:
        xor edi,edi
    L_0042cd70:
        lea esi,[edi+5AB0h]
    L_0042cd76:
        call asm_Platform_StopWorker_0044c150
    L_0042cd7b:
        lea eax,[esi+8]
    L_0042cd7e:
        push eax
    L_0042cd7f:
        push 0
    L_0042cd81:
        push edi
    L_0042cd82:
        push 42C9F0h
    L_0042cd87:
        push 0
    L_0042cd89:
        push 0
    L_0042cd8b:
        mov dword ptr [esi+18h],42C9F0h
    L_0042cd92:
        mov dword ptr [esi+10h],1
    L_0042cd99:
        mov dword ptr [esi+0Ch],0
    L_0042cda0:
        call asm_beginthreadex_00453683
    L_0042cda5:
        add esp,18h
    L_0042cda8:
        mov dword ptr [esi+4],eax
    L_0042cdab:
        mov eax,edi
    L_0042cdad:
        pop edi
    L_0042cdae:
        pop esi
    L_0042cdaf:
        ret
    }
}
