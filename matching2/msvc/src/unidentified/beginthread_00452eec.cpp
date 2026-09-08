#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452EEC..0x00452F7C: __beginthread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_beginthread_00452eec() {
    __asm {
    L_00452eec:
        push ebx
    L_00452eed:
        push edi
    L_00452eee:
        mov edi,dword ptr [esp+0Ch]
    L_00452ef2:
        xor ebx,ebx
    L_00452ef4:
        test edi,edi
    L_00452ef6:
        jne short L_00452f08
    L_00452ef8:
        call asm_FUN_00456af2_00456af2
    L_00452efd:
        mov dword ptr [eax],16h
    L_00452f03:
        or eax,0FFFFFFFFh
    L_00452f06:
        jmp short L_00452f7a
    L_00452f08:
        push esi
    L_00452f09:
        push 8Ch
    L_00452f0e:
        push 1
    L_00452f10:
        call asm_FUN_0045794d_0045794d
    L_00452f15:
        mov esi,eax
    L_00452f17:
        test esi,esi
    L_00452f19:
        pop ecx
    L_00452f1a:
        pop ecx
    L_00452f1b:
        je short L_00452f60
    L_00452f1d:
        push esi
    L_00452f1e:
        call asm_initptd_00456344
    L_00452f23:
        mov eax,dword ptr [esp+1Ch]
    L_00452f27:
        pop ecx
    L_00452f28:
        push esi
    L_00452f29:
        push 4
    L_00452f2b:
        push esi
    L_00452f2c:
        push 452E5Ah
    L_00452f31:
        push dword ptr [esp+24h]
    L_00452f35:
        mov dword ptr [esi+4Ch],edi
    L_00452f38:
        push 0
    L_00452f3a:
        mov dword ptr [esi+50h],eax
    L_00452f3d:
        call dword ptr [data_00466118]
    L_00452f43:
        mov edi,eax
    L_00452f45:
        test edi,edi
    L_00452f47:
        mov dword ptr [esi+4],edi
    L_00452f4a:
        je short L_00452f58
    L_00452f4c:
        push edi
    L_00452f4d:
        call dword ptr [data_00466130]
    L_00452f53:
        cmp eax,0FFFFFFFFh
    L_00452f56:
        jne short L_00452f77
    L_00452f58:
        call dword ptr [data_0046610c]
    L_00452f5e:
        mov ebx,eax
    L_00452f60:
        push esi
    L_00452f61:
        call asm_free_00452422
    L_00452f66:
        test ebx,ebx
    L_00452f68:
        pop ecx
    L_00452f69:
        je short L_00452f72
    L_00452f6b:
        push ebx
    L_00452f6c:
        call asm_dosmaperr_00456b04
    L_00452f71:
        pop ecx
    L_00452f72:
        or eax,0FFFFFFFFh
    L_00452f75:
        jmp short L_00452f79
    L_00452f77:
        mov eax,edi
    L_00452f79:
        pop esi
    L_00452f7a:
        pop edi
    L_00452f7b:
        pop ebx
    L_00452f7c:
        ret
    }
}
