#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A50..0x00449A8F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a50() {
    __asm {
    L_00449a50:
        mov edx,dword ptr [eax+4]
    L_00449a53:
        xor ecx,ecx
    L_00449a55:
        mov dword ptr [eax+8],ecx
    L_00449a58:
        mov dword ptr [eax+0Ch],ecx
    L_00449a5b:
        mov dword ptr [eax+10h],ecx
    L_00449a5e:
        mov dword ptr [eax],ecx
    L_00449a60:
        and edx,0FFFFFFFEh
    L_00449a63:
        mov dword ptr [eax+4],edx
    L_00449a66:
        mov dword ptr [eax+14h],eax
    L_00449a69:
        mov dword ptr [eax+18h],ecx
    L_00449a6c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a6f:
        ret
    L_00449a70:
        mov edx,dword ptr [eax+4]
    L_00449a73:
        mov dword ptr [eax+8],ecx
    L_00449a76:
        xor ecx,ecx
    L_00449a78:
        mov dword ptr [eax+0Ch],ecx
    L_00449a7b:
        mov dword ptr [eax+10h],ecx
    L_00449a7e:
        mov dword ptr [eax],ecx
    L_00449a80:
        and edx,0FFFFFFFEh
    L_00449a83:
        mov dword ptr [eax+4],edx
    L_00449a86:
        mov dword ptr [eax+14h],eax
    L_00449a89:
        mov dword ptr [eax+18h],ecx
    L_00449a8c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a8f:
        ret
    }
}
