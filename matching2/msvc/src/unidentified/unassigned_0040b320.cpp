#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B320..0x0040B368: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b320() {
    __asm {
    L_0040b320:
        push esi
    L_0040b321:
        mov esi,eax
    L_0040b323:
        test byte ptr [esi+28h],1
    L_0040b327:
        jne short L_0040b347
    L_0040b329:
        mov eax,dword ptr [esi+18h]
    L_0040b32c:
        mov ecx,dword ptr [esi+1Ch]
    L_0040b32f:
        push eax
    L_0040b330:
        push ecx
    L_0040b331:
        lea ecx,[esi+0Ch]
    L_0040b334:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0040b339:
        mov dword ptr [esi+14h],0
    L_0040b340:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040b345:
        pop esi
    L_0040b346:
        ret
    L_0040b347:
        fld dword ptr [esi+24h]
    L_0040b34a:
        push ecx
    L_0040b34b:
        fadd dword ptr [esi+20h]
    L_0040b34e:
        fstp dword ptr [esi+20h]
    L_0040b351:
        fld dword ptr [esi+18h]
    L_0040b354:
        fadd dword ptr [esi+1Ch]
    L_0040b357:
        fstp dword ptr [esp]
    L_0040b35a:
        call asm_Angle_Normalize_0044bc70
    L_0040b35f:
        fstp dword ptr [esi+1Ch]
    L_0040b362:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040b367:
        pop esi
    L_0040b368:
        ret
    }
}
