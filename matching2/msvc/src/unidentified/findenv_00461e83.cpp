#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461E83..0x00461ECF: findenv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_findenv_00461e83() {
    __asm {
    L_00461e83:
        push esi
    L_00461e84:
        mov esi,dword ptr [data_00477490]
    L_00461e8a:
        jmp short L_00461eae
    L_00461e8c:
        push edi
    L_00461e8d:
        push eax
    L_00461e8e:
        push dword ptr [esp+10h]
    L_00461e92:
        call asm_mbsnbicoll_004610a6
    L_00461e97:
        add esp,0Ch
    L_00461e9a:
        test eax,eax
    L_00461e9c:
        jne short L_00461eab
    L_00461e9e:
        mov eax,dword ptr [esi]
    L_00461ea0:
        mov al,byte ptr [edi+eax]
    L_00461ea3:
        cmp al,3Dh
    L_00461ea5:
        je short L_00461ec3
    L_00461ea7:
        test al,al
    L_00461ea9:
        je short L_00461ec3
    L_00461eab:
        add esi,4
    L_00461eae:
        mov eax,dword ptr [esi]
    L_00461eb0:
        test eax,eax
    L_00461eb2:
        jne short L_00461e8c
    L_00461eb4:
        mov eax,esi
    L_00461eb6:
        sub eax,dword ptr [data_00477490]
    L_00461ebc:
        pop esi
    L_00461ebd:
        sar eax,2
    L_00461ec0:
        neg eax
    L_00461ec2:
        ret
    L_00461ec3:
        mov eax,esi
    L_00461ec5:
        sub eax,dword ptr [data_00477490]
    L_00461ecb:
        pop esi
    L_00461ecc:
        sar eax,2
    L_00461ecf:
        ret
    }
}
