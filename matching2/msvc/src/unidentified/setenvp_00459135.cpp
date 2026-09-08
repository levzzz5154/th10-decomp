#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459135..0x004591FB: __setenvp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_setenvp_00459135() {
    __asm {
    L_00459135:
        push ebx
    L_00459136:
        xor ebx,ebx
    L_00459138:
        cmp dword ptr [data_00499314],ebx
    L_0045913e:
        push esi
    L_0045913f:
        push edi
    L_00459140:
        jne short L_00459147
    L_00459142:
        call asm_initmbctable_0045d2ac
    L_00459147:
        mov esi,dword ptr [data_00477204]
    L_0045914d:
        xor edi,edi
    L_0045914f:
        cmp esi,ebx
    L_00459151:
        jne short L_00459165
    L_00459153:
        jmp short L_00459185
    L_00459155:
        cmp al,3Dh
    L_00459157:
        je short L_0045915a
    L_00459159:
        inc edi
    L_0045915a:
        push esi
    L_0045915b:
        call asm_strlen_00456720
    L_00459160:
        pop ecx
    L_00459161:
        lea esi,[esi+eax+1]
    L_00459165:
        mov al,byte ptr [esi]
    L_00459167:
        cmp al,bl
    L_00459169:
        jne short L_00459155
    L_0045916b:
        lea eax,[edi*4+4]
    L_00459172:
        push eax
    L_00459173:
        call asm_malloc_00452706
    L_00459178:
        mov edi,eax
    L_0045917a:
        cmp edi,ebx
    L_0045917c:
        pop ecx
    L_0045917d:
        mov dword ptr [data_00477490],edi
    L_00459183:
        jne short L_0045918a
    L_00459185:
        or eax,0FFFFFFFFh
    L_00459188:
        jmp short L_004591e2
    L_0045918a:
        mov esi,dword ptr [data_00477204]
    L_00459190:
        push ebp
    L_00459191:
        jmp short L_004591bd
    L_00459193:
        push esi
    L_00459194:
        call asm_strlen_00456720
    L_00459199:
        mov ebp,eax
    L_0045919b:
        inc ebp
    L_0045919c:
        cmp byte ptr [esi],3Dh
    L_0045919f:
        pop ecx
    L_004591a0:
        je short L_004591bb
    L_004591a2:
        push ebp
    L_004591a3:
        call asm_malloc_00452706
    L_004591a8:
        cmp eax,ebx
    L_004591aa:
        pop ecx
    L_004591ab:
        mov dword ptr [edi],eax
    L_004591ad:
        je short L_004591e6
    L_004591af:
        push esi
    L_004591b0:
        push eax
    L_004591b1:
        call asm_FUN_0045bd80_0045bd80
    L_004591b6:
        pop ecx
    L_004591b7:
        pop ecx
    L_004591b8:
        add edi,4
    L_004591bb:
        add esi,ebp
    L_004591bd:
        cmp byte ptr [esi],bl
    L_004591bf:
        jne short L_00459193
    L_004591c1:
        push dword ptr [data_00477204]
    L_004591c7:
        call asm_free_00452422
    L_004591cc:
        mov dword ptr [data_00477204],ebx
    L_004591d2:
        mov dword ptr [edi],ebx
    L_004591d4:
        mov dword ptr [data_00499308],1
    L_004591de:
        xor eax,eax
    L_004591e0:
        pop ecx
    L_004591e1:
        pop ebp
    L_004591e2:
        pop edi
    L_004591e3:
        pop esi
    L_004591e4:
        pop ebx
    L_004591e5:
        ret
    L_004591e6:
        push dword ptr [data_00477490]
    L_004591ec:
        call asm_free_00452422
    L_004591f1:
        mov dword ptr [data_00477490],ebx
    L_004591f7:
        or eax,0FFFFFFFFh
    L_004591fa:
        jmp short L_004591e0
    }
}
