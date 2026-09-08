#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DCF0..0x0044DD23: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044dcf0() {
    __asm {
    L_0044dcf0:
        mov dword ptr [eax+90h],edx
    L_0044dcf6:
        mov edx,dword ptr [esp+4]
    L_0044dcfa:
        mov dword ptr [eax+88h],edx
    L_0044dd00:
        mov dword ptr [eax+80h],ecx
    L_0044dd06:
        mov dword ptr [eax+84h],ecx
    L_0044dd0c:
        mov dword ptr [eax+7Ch],1
    L_0044dd13:
        mov eax,dword ptr [esp+8]
    L_0044dd17:
        dec eax
    L_0044dd18:
        neg eax
    L_0044dd1a:
        sbb eax,eax
    L_0044dd1c:
        and eax,80004001h
    L_0044dd21:
        ret 8
    }
}
