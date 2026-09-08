#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004246C0..0x004247B3: FUN_004246c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004246c0_004246c0() {
    __asm {
    L_004246c0:
        mov ecx,dword ptr [esi+80h]
    L_004246c6:
        lea edx,[esi+14h]
    L_004246c9:
        push ebx
    L_004246ca:
        mov ebx,0FFFFFFFEh
    L_004246cf:
        and ecx,ebx
    L_004246d1:
        mov dword ptr [edx+6Ch],ecx
    L_004246d4:
        and dword ptr [edx+0B0h],ebx
    L_004246da:
        push edi
    L_004246db:
        and dword ptr [edx+0FCh],ebx
    L_004246e1:
        and dword ptr [edx+128h],ebx
    L_004246e7:
        and dword ptr [edx+174h],ebx
    L_004246ed:
        and dword ptr [edx+1B0h],ebx
    L_004246f3:
        and dword ptr [edx+1FCh],ebx
    L_004246f9:
        and dword ptr [edx+228h],ebx
    L_004246ff:
        and dword ptr [edx+378h],ebx
    L_00424705:
        xor eax,eax
    L_00424707:
        mov edi,edx
    L_00424709:
        mov ecx,0EBh
    L_0042470e:
        rep stosd
    L_00424710:
        mov word ptr [edx+384h],0FFFFh
    L_00424719:
        and dword ptr [esi+470h],ebx
    L_0042471f:
        and dword ptr [esi+484h],ebx
    L_00424725:
        and dword ptr [esi+498h],ebx
    L_0042472b:
        lea eax,[esi+4ACh]
    L_00424731:
        mov ecx,80h
    L_00424736:
        and dword ptr [eax],ebx
    L_00424738:
        add eax,5Ch
    L_0042473b:
        dec ecx
    L_0042473c:
        jne short L_00424736
    L_0042473e:
        mov edi,dword ptr [esi+3320h]
    L_00424744:
        lea eax,[esi+32A0h]
    L_0042474a:
        and edi,ebx
    L_0042474c:
        mov dword ptr [eax+80h],edi
    L_00424752:
        mov ecx,dword ptr [eax+118h]
    L_00424758:
        add eax,98h
    L_0042475d:
        and ecx,ebx
    L_0042475f:
        mov dword ptr [eax+80h],ecx
    L_00424765:
        mov edx,dword ptr [eax+118h]
    L_0042476b:
        add eax,98h
    L_00424770:
        and edx,ebx
    L_00424772:
        mov dword ptr [eax+80h],edx
    L_00424778:
        and dword ptr [eax+118h],ebx
    L_0042477e:
        lea eax,[esi+3560h]
    L_00424784:
        mov ecx,21h
    L_00424789:
        lea esp,[esp+force_disp32_zero]
    L_00424790:
        and dword ptr [eax],ebx
    L_00424792:
        add eax,6Ch
    L_00424795:
        dec ecx
    L_00424796:
        jne short L_00424790
    L_00424798:
        and dword ptr [esi+431Ch],ebx
    L_0042479e:
        xor eax,eax
    L_004247a0:
        mov ecx,111Eh
    L_004247a5:
        mov edi,esi
    L_004247a7:
        rep stosd
    L_004247a9:
        pop edi
    L_004247aa:
        mov dword ptr [data_00477834],esi
    L_004247b0:
        mov eax,esi
    L_004247b2:
        pop ebx
    L_004247b3:
        ret
    }
}
