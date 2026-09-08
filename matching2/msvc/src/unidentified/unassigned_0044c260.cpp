#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C260..0x0044C299: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c260() {
    __asm {
    L_0044c260:
        test byte ptr [esi+28h],1
    L_0044c264:
        jne short L_0044c27e
    L_0044c266:
        mov eax,dword ptr [esi+18h]
    L_0044c269:
        mov ecx,dword ptr [esi+1Ch]
    L_0044c26c:
        push eax
    L_0044c26d:
        push ecx
    L_0044c26e:
        lea ecx,[esi+0Ch]
    L_0044c271:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0044c276:
        mov dword ptr [esi+14h],0
    L_0044c27d:
        ret
    L_0044c27e:
        fld dword ptr [esi+24h]
    L_0044c281:
        push ecx
    L_0044c282:
        fadd dword ptr [esi+20h]
    L_0044c285:
        fstp dword ptr [esi+20h]
    L_0044c288:
        fld dword ptr [esi+18h]
    L_0044c28b:
        fadd dword ptr [esi+1Ch]
    L_0044c28e:
        fstp dword ptr [esp]
    L_0044c291:
        call asm_Angle_Normalize_0044bc70
    L_0044c296:
        fstp dword ptr [esi+1Ch]
    L_0044c299:
        ret
    }
}
