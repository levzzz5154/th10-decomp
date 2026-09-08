#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E063..0x0045E0E3: __getenv_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_getenv_lk_0045e063() {
    __asm {
    L_0045e063:
        cmp dword ptr [data_00499308],0
    L_0045e06a:
        push esi
    L_0045e06b:
        mov esi,dword ptr [data_00477490]
    L_0045e071:
        jne short L_0045e077
    L_0045e073:
        xor eax,eax
    L_0045e075:
        pop esi
    L_0045e076:
        ret
    L_0045e077:
        test esi,esi
    L_0045e079:
        push ebx
    L_0045e07a:
        push edi
    L_0045e07b:
        jne short L_0045e098
    L_0045e07d:
        cmp dword ptr [data_00477498],esi
    L_0045e083:
        je short L_0045e0d6
    L_0045e085:
        call asm_wtomb_environ_004610f4
    L_0045e08a:
        test eax,eax
    L_0045e08c:
        jne short L_0045e0d6
    L_0045e08e:
        mov esi,dword ptr [data_00477490]
    L_0045e094:
        test esi,esi
    L_0045e096:
        je short L_0045e0d6
    L_0045e098:
        mov ebx,dword ptr [esp+10h]
    L_0045e09c:
        test ebx,ebx
    L_0045e09e:
        je short L_0045e0d6
    L_0045e0a0:
        push ebx
    L_0045e0a1:
        call asm_strlen_00456720
    L_0045e0a6:
        pop ecx
    L_0045e0a7:
        mov edi,eax
    L_0045e0a9:
        jmp short L_0045e0d0
    L_0045e0ab:
        push eax
    L_0045e0ac:
        call asm_strlen_00456720
    L_0045e0b1:
        cmp eax,edi
    L_0045e0b3:
        pop ecx
    L_0045e0b4:
        jbe short L_0045e0cd
    L_0045e0b6:
        mov eax,dword ptr [esi]
    L_0045e0b8:
        cmp byte ptr [eax+edi],3Dh
    L_0045e0bc:
        jne short L_0045e0cd
    L_0045e0be:
        push edi
    L_0045e0bf:
        push ebx
    L_0045e0c0:
        push eax
    L_0045e0c1:
        call asm_mbsnbicoll_004610a6
    L_0045e0c6:
        add esp,0Ch
    L_0045e0c9:
        test eax,eax
    L_0045e0cb:
        je short L_0045e0dc
    L_0045e0cd:
        add esi,4
    L_0045e0d0:
        mov eax,dword ptr [esi]
    L_0045e0d2:
        test eax,eax
    L_0045e0d4:
        jne short L_0045e0ab
    L_0045e0d6:
        xor eax,eax
    L_0045e0d8:
        pop edi
    L_0045e0d9:
        pop ebx
    L_0045e0da:
        pop esi
    L_0045e0db:
        ret
    L_0045e0dc:
        mov eax,dword ptr [esi]
    L_0045e0de:
        lea eax,[eax+edi+1]
    L_0045e0e2:
        jmp short L_0045e0d8
    }
}
