#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BB30..0x0042BBC0: FUN_0042bb30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bb30_0042bb30() {
    __asm {
    L_0042bb30:
        xor eax,eax
    L_0042bb32:
        mov dword ptr [edx+14h],eax
    L_0042bb35:
        mov dword ptr [edx+18h],eax
    L_0042bb38:
        mov dword ptr [edx+1Ch],eax
    L_0042bb3b:
        mov dword ptr [edx+20h],eax
    L_0042bb3e:
        mov dword ptr [edx+10h],4703E4h
    L_0042bb45:
        mov dword ptr [edx+0C8h],eax
    L_0042bb4b:
        mov dword ptr [edx+3Ch],eax
    L_0042bb4e:
        mov dword ptr [edx+110h],eax
    L_0042bb54:
        mov dword ptr [edx+10Ch],1
    L_0042bb5e:
        mov ecx,3E7h
    L_0042bb63:
        mov dword ptr [edx+44h],ecx
    L_0042bb66:
        mov dword ptr [edx+1A0h],eax
    L_0042bb6c:
        mov dword ptr [edx+114h],eax
    L_0042bb72:
        mov dword ptr [edx+1E8h],eax
    L_0042bb78:
        mov dword ptr [edx+11Ch],ecx
    L_0042bb7e:
        mov dword ptr [edx+1E4h],1
    L_0042bb88:
        mov dword ptr [edx+1F4h],ecx
    L_0042bb8e:
        push edi
    L_0042bb8f:
        mov dword ptr [edx+278h],eax
    L_0042bb95:
        mov dword ptr [edx+1ECh],eax
    L_0042bb9b:
        mov dword ptr [edx+2C0h],eax
    L_0042bba1:
        mov dword ptr [edx+2BCh],1
    L_0042bbab:
        mov ecx,0B9h
    L_0042bbb0:
        mov edi,edx
    L_0042bbb2:
        rep stosd
    L_0042bbb4:
        or dword ptr [edx],2
    L_0042bbb7:
        mov dword ptr [data_00477844],edx
    L_0042bbbd:
        mov eax,edx
    L_0042bbbf:
        pop edi
    L_0042bbc0:
        ret
    }
}
