#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418D40..0x00418E2C: StageTipManager_Construct
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTipManager_Construct_00418d40() {
    __asm {
    L_00418d40:
        xor eax,eax
    L_00418d42:
        push edi
    L_00418d43:
        mov ecx,6Ah
    L_00418d48:
        mov edi,edx
    L_00418d4a:
        rep stosd
    L_00418d4c:
        or dword ptr [edx],2
    L_00418d4f:
        mov dword ptr [edx+18h],edx
    L_00418d52:
        mov dword ptr [edx+24h],edx
    L_00418d55:
        xor eax,eax
    L_00418d57:
        mov dword ptr [edx+1Ch],eax
    L_00418d5a:
        mov dword ptr [edx+20h],eax
    L_00418d5d:
        mov dword ptr [edx+28h],eax
    L_00418d60:
        mov dword ptr [edx+2Ch],eax
    L_00418d63:
        mov dword ptr [edx+30h],edx
    L_00418d66:
        mov dword ptr [edx+34h],eax
    L_00418d69:
        mov dword ptr [edx+38h],eax
    L_00418d6c:
        mov dword ptr [edx+3Ch],edx
    L_00418d6f:
        mov dword ptr [edx+40h],eax
    L_00418d72:
        mov dword ptr [edx+44h],eax
    L_00418d75:
        mov dword ptr [edx+48h],edx
    L_00418d78:
        mov dword ptr [edx+4Ch],eax
    L_00418d7b:
        mov dword ptr [edx+50h],eax
    L_00418d7e:
        mov dword ptr [edx+54h],edx
    L_00418d81:
        mov dword ptr [edx+58h],eax
    L_00418d84:
        mov dword ptr [edx+5Ch],eax
    L_00418d87:
        mov dword ptr [edx+60h],edx
    L_00418d8a:
        mov dword ptr [edx+64h],eax
    L_00418d8d:
        mov dword ptr [edx+68h],eax
    L_00418d90:
        mov dword ptr [edx+6Ch],edx
    L_00418d93:
        mov dword ptr [edx+70h],eax
    L_00418d96:
        mov dword ptr [edx+74h],eax
    L_00418d99:
        mov dword ptr [edx+78h],edx
    L_00418d9c:
        mov dword ptr [edx+84h],edx
    L_00418da2:
        mov dword ptr [edx+7Ch],eax
    L_00418da5:
        mov dword ptr [edx+80h],eax
    L_00418dab:
        mov dword ptr [edx+88h],eax
    L_00418db1:
        mov dword ptr [edx+8Ch],eax
    L_00418db7:
        mov dword ptr [edx+90h],edx
    L_00418dbd:
        mov dword ptr [edx+94h],eax
    L_00418dc3:
        mov dword ptr [edx+98h],eax
    L_00418dc9:
        mov dword ptr [edx+9Ch],edx
    L_00418dcf:
        mov dword ptr [edx+0A0h],eax
    L_00418dd5:
        mov dword ptr [edx+0A4h],eax
    L_00418ddb:
        mov dword ptr [edx+0A8h],edx
    L_00418de1:
        mov dword ptr [edx+0ACh],eax
    L_00418de7:
        mov dword ptr [edx+0B0h],eax
    L_00418ded:
        mov dword ptr [edx+0B4h],edx
    L_00418df3:
        mov dword ptr [edx+0B8h],eax
    L_00418df9:
        mov dword ptr [edx+0BCh],eax
    L_00418dff:
        mov dword ptr [edx+0C0h],edx
    L_00418e05:
        mov dword ptr [edx+0C4h],eax
    L_00418e0b:
        mov dword ptr [edx+0C8h],eax
    L_00418e11:
        mov dword ptr [edx+0CCh],edx
    L_00418e17:
        mov dword ptr [edx+0D0h],eax
    L_00418e1d:
        mov dword ptr [edx+0D4h],eax
    L_00418e23:
        mov dword ptr [data_00477814],edx
    L_00418e29:
        mov eax,edx
    L_00418e2b:
        pop edi
    L_00418e2c:
        ret
    }
}



