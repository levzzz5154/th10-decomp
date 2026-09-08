#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F00..0x00401F36: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401f00() {
    __asm {
    L_00401f00:
        xor ecx,ecx
    L_00401f02:
        mov dword ptr [eax+38h],ecx
    L_00401f05:
        mov dword ptr [eax+34h],ecx
    L_00401f08:
        mov dword ptr [eax+30h],ecx
    L_00401f0b:
        mov dword ptr [eax+2Ch],ecx
    L_00401f0e:
        mov dword ptr [eax+24h],ecx
    L_00401f11:
        mov dword ptr [eax+20h],ecx
    L_00401f14:
        mov dword ptr [eax+1Ch],ecx
    L_00401f17:
        mov dword ptr [eax+18h],ecx
    L_00401f1a:
        mov dword ptr [eax+10h],ecx
    L_00401f1d:
        mov dword ptr [eax+0Ch],ecx
    L_00401f20:
        mov dword ptr [eax+8],ecx
    L_00401f23:
        mov dword ptr [eax+4],ecx
    L_00401f26:
        mov ecx,3F800000h
    L_00401f2b:
        mov dword ptr [eax+3Ch],ecx
    L_00401f2e:
        mov dword ptr [eax+28h],ecx
    L_00401f31:
        mov dword ptr [eax+14h],ecx
    L_00401f34:
        mov dword ptr [eax],ecx
    L_00401f36:
        ret
    }
}
