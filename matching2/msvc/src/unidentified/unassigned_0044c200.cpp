#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C200..0x0044C237: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c200() {
    __asm {
    L_0044c200:
        push esi
    L_0044c201:
        mov esi,eax
    L_0044c203:
        call asm_Platform_StopWorker_0044c150
    L_0044c208:
        mov ecx,dword ptr [esp+8]
    L_0044c20c:
        lea eax,[esi+8]
    L_0044c20f:
        push eax
    L_0044c210:
        push 4
    L_0044c212:
        push ecx
    L_0044c213:
        push edi
    L_0044c214:
        push 0
    L_0044c216:
        push 0
    L_0044c218:
        mov dword ptr [esi+18h],edi
    L_0044c21b:
        mov dword ptr [esi+10h],1
    L_0044c222:
        mov dword ptr [esi+0Ch],0
    L_0044c229:
        call asm_beginthreadex_00453683
    L_0044c22e:
        add esp,18h
    L_0044c231:
        mov dword ptr [esi+4],eax
    L_0044c234:
        pop esi
    L_0044c235:
        ret 4
    }
}
