#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453FDD..0x00454093: ___sbh_alloc_new_region
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_alloc_new_region_00453fdd() {
    __asm {
    L_00453fdd:
        mov eax,dword ptr [data_00499328]
    L_00453fe2:
        mov ecx,dword ptr [data_00499338]
    L_00453fe8:
        push edi
    L_00453fe9:
        xor edi,edi
    L_00453feb:
        cmp eax,ecx
    L_00453fed:
        jne short L_00454023
    L_00453fef:
        lea eax,[ecx+ecx*4+50h]
    L_00453ff3:
        shl eax,2
    L_00453ff6:
        push eax
    L_00453ff7:
        push dword ptr [data_0049932c]
    L_00453ffd:
        push edi
    L_00453ffe:
        push dword ptr [data_00499340]
    L_00454004:
        call dword ptr [data_00466178]
    L_0045400a:
        cmp eax,edi
    L_0045400c:
        jne short L_00454012
    L_0045400e:
        xor eax,eax
    L_00454010:
        pop edi
    L_00454011:
        ret
    L_00454012:
        add dword ptr [data_00499338],10h
    L_00454019:
        mov dword ptr [data_0049932c],eax
    L_0045401e:
        mov eax,dword ptr [data_00499328]
    L_00454023:
        mov ecx,dword ptr [data_0049932c]
    L_00454029:
        push esi
    L_0045402a:
        push 41C4h
    L_0045402f:
        push 8
    L_00454031:
        push dword ptr [data_00499340]
    L_00454037:
        lea eax,[eax+eax*4]
    L_0045403a:
        lea esi,[ecx+eax*4]
    L_0045403d:
        call dword ptr [data_004661e4]
    L_00454043:
        cmp eax,edi
    L_00454045:
        mov dword ptr [esi+10h],eax
    L_00454048:
        jne short L_0045404e
    L_0045404a:
        xor eax,eax
    L_0045404c:
        jmp short L_00454091
    L_0045404e:
        push 4
    L_00454050:
        push 2000h
    L_00454055:
        push 100000h
    L_0045405a:
        push edi
    L_0045405b:
        call dword ptr [data_0046617c]
    L_00454061:
        cmp eax,edi
    L_00454063:
        mov dword ptr [esi+0Ch],eax
    L_00454066:
        jne short L_0045407a
    L_00454068:
        push dword ptr [esi+10h]
    L_0045406b:
        push edi
    L_0045406c:
        push dword ptr [data_00499340]
    L_00454072:
        call dword ptr [data_004661e8]
    L_00454078:
        jmp short L_0045404a
    L_0045407a:
        or dword ptr [esi+8],0FFFFFFFFh
    L_0045407e:
        mov dword ptr [esi],edi
    L_00454080:
        mov dword ptr [esi+4],edi
    L_00454083:
        inc dword ptr [data_00499328]
    L_00454089:
        mov eax,dword ptr [esi+10h]
    L_0045408c:
        or dword ptr [eax],0FFFFFFFFh
    L_0045408f:
        mov eax,esi
    L_00454091:
        pop esi
    L_00454092:
        pop edi
    L_00454093:
        ret
    }
}
