#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C1C0..0x0044C1F7: FUN_0044c1c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c1c0_0044c1c0() {
    __asm {
    L_0044c1c0:
        push esi
    L_0044c1c1:
        mov esi,eax
    L_0044c1c3:
        call asm_Platform_StopWorker_0044c150
    L_0044c1c8:
        mov ecx,dword ptr [esp+8]
    L_0044c1cc:
        lea eax,[esi+8]
    L_0044c1cf:
        push eax
    L_0044c1d0:
        push 0
    L_0044c1d2:
        push ecx
    L_0044c1d3:
        push edi
    L_0044c1d4:
        push 0
    L_0044c1d6:
        push 0
    L_0044c1d8:
        mov dword ptr [esi+18h],edi
    L_0044c1db:
        mov dword ptr [esi+10h],1
    L_0044c1e2:
        mov dword ptr [esi+0Ch],0
    L_0044c1e9:
        call asm_beginthreadex_00453683
    L_0044c1ee:
        add esp,18h
    L_0044c1f1:
        mov dword ptr [esi+4],eax
    L_0044c1f4:
        pop esi
    L_0044c1f5:
        ret 4
    }
}
