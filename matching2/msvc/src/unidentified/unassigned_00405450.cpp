#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405450..0x00405488: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405450() {
    __asm {
    L_00405450:
        mov ecx,dword ptr [eax+10h]
    L_00405453:
        test cl,1
    L_00405456:
        push esi
    L_00405457:
        mov esi,dword ptr [esp+8]
    L_0040545b:
        jne short L_00405478
    L_0040545d:
        xor edx,edx
    L_0040545f:
        or ecx,1
    L_00405462:
        mov dword ptr [eax+4],edx
    L_00405465:
        mov dword ptr [eax],0FFF0BDC1h
    L_0040546b:
        mov dword ptr [eax+8],edx
    L_0040546e:
        mov dword ptr [eax+0Ch],476F78h
    L_00405475:
        mov dword ptr [eax+10h],ecx
    L_00405478:
        fild dword ptr [esp+8]
    L_0040547c:
        mov dword ptr [eax+4],esi
    L_0040547f:
        dec esi
    L_00405480:
        mov dword ptr [eax],esi
    L_00405482:
        fstp dword ptr [eax+8]
    L_00405485:
        pop esi
    L_00405486:
        ret 4
    }
}
