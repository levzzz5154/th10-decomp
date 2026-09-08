#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FA1A..0x0045FA9C: __lseeki64_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lseeki64_lk_0045fa1a() {
    __asm {
    L_0045fa1a:
        push ebp
    L_0045fa1b:
        mov ebp,esp
    L_0045fa1d:
        push ecx
    L_0045fa1e:
        push ecx
    L_0045fa1f:
        mov eax,dword ptr [ebp+0Ch]
    L_0045fa22:
        push esi
    L_0045fa23:
        mov esi,dword ptr [ebp+8]
    L_0045fa26:
        mov dword ptr [ebp-8],eax
    L_0045fa29:
        mov eax,dword ptr [ebp+10h]
    L_0045fa2c:
        push edi
    L_0045fa2d:
        push esi
    L_0045fa2e:
        mov dword ptr [ebp-4],eax
    L_0045fa31:
        call asm_get_osfhandle_0045f6d4
    L_0045fa36:
        or edi,0FFFFFFFFh
    L_0045fa39:
        cmp eax,edi
    L_0045fa3b:
        pop ecx
    L_0045fa3c:
        jne short L_0045fa4b
    L_0045fa3e:
        call asm_FUN_00456af2_00456af2
    L_0045fa43:
        mov dword ptr [eax],9
    L_0045fa49:
        jmp short L_0045fa74
    L_0045fa4b:
        push dword ptr [ebp+14h]
    L_0045fa4e:
        lea ecx,[ebp-4]
    L_0045fa51:
        push ecx
    L_0045fa52:
        push dword ptr [ebp-8]
    L_0045fa55:
        push eax
    L_0045fa56:
        call dword ptr [data_004660c8]
    L_0045fa5c:
        cmp eax,edi
    L_0045fa5e:
        mov dword ptr [ebp-8],eax
    L_0045fa61:
        jne short L_0045fa7a
    L_0045fa63:
        call dword ptr [data_0046610c]
    L_0045fa69:
        test eax,eax
    L_0045fa6b:
        je short L_0045fa7a
    L_0045fa6d:
        push eax
    L_0045fa6e:
        call asm_dosmaperr_00456b04
    L_0045fa73:
        pop ecx
    L_0045fa74:
        mov eax,edi
    L_0045fa76:
        mov edx,edi
    L_0045fa78:
        jmp short L_0045fa99
    L_0045fa7a:
        mov eax,esi
    L_0045fa7c:
        sar eax,5
    L_0045fa7f:
        mov eax,dword ptr [eax*4+499200h]
    L_0045fa86:
        and esi,1Fh
    L_0045fa89:
        lea ecx,[esi+esi*8]
    L_0045fa8c:
        lea eax,[eax+ecx*4+4]
    L_0045fa90:
        and byte ptr [eax],0FDh
    L_0045fa93:
        mov eax,dword ptr [ebp-8]
    L_0045fa96:
        mov edx,dword ptr [ebp-4]
    L_0045fa99:
        pop edi
    L_0045fa9a:
        pop esi
    L_0045fa9b:
        leave
    L_0045fa9c:
        ret
    }
}
