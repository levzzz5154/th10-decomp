#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AC20..0x0042AC56: FUN_0042ac20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042ac20_0042ac20() {
    __asm {
    L_0042ac20:
        mov eax,ecx
    L_0042ac22:
        xor ecx,ecx
    L_0042ac24:
        mov edx,eax
    L_0042ac26:
        mov dword ptr [edx],ecx
    L_0042ac28:
        mov dword ptr [edx+4],ecx
    L_0042ac2b:
        mov dword ptr [edx+8],ecx
    L_0042ac2e:
        mov dword ptr [edx+0Ch],ecx
    L_0042ac31:
        mov dword ptr [edx+10h],ecx
    L_0042ac34:
        mov dword ptr [edx+14h],ecx
    L_0042ac37:
        mov dword ptr [edx+18h],ecx
    L_0042ac3a:
        mov dword ptr [edx+1Ch],ecx
    L_0042ac3d:
        mov dword ptr [edx+20h],ecx
    L_0042ac40:
        mov ecx,dword ptr [eax]
    L_0042ac42:
        mov edx,dword ptr [eax+8]
    L_0042ac45:
        mov dword ptr [eax+4],ecx
    L_0042ac48:
        mov dword ptr [eax+0Ch],edx
    L_0042ac4b:
        xor ecx,ecx
    L_0042ac4d:
        mov dword ptr [eax+18h],eax
    L_0042ac50:
        mov dword ptr [eax+1Ch],ecx
    L_0042ac53:
        mov dword ptr [eax+20h],ecx
    L_0042ac56:
        ret
    }
}
