#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BAD0..0x0042BB25: FUN_0042bad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bad0_0042bad0() {
    __asm {
    L_0042bad0:
        mov eax,dword ptr [esi+34h]
    L_0042bad3:
        test eax,eax
    L_0042bad5:
        je short L_0042bb25
    L_0042bad7:
        mov eax,dword ptr [esi+38h]
    L_0042bada:
        push edi
    L_0042badb:
        xor edi,edi
    L_0042badd:
        test eax,eax
    L_0042badf:
        jle short L_0042bb06
    L_0042bae1:
        mov eax,dword ptr [esi+34h]
    L_0042bae4:
        mov eax,dword ptr [eax+edi*4]
    L_0042bae7:
        test eax,eax
    L_0042bae9:
        je short L_0042bafe
    L_0042baeb:
        push eax
    L_0042baec:
        call asm_free_00452422
    L_0042baf1:
        mov ecx,dword ptr [esi+34h]
    L_0042baf4:
        add esp,4
    L_0042baf7:
        mov dword ptr [ecx+edi*4],0
    L_0042bafe:
        mov eax,dword ptr [esi+38h]
    L_0042bb01:
        inc edi
    L_0042bb02:
        cmp edi,eax
    L_0042bb04:
        jl short L_0042bae1
    L_0042bb06:
        mov eax,dword ptr [esi+34h]
    L_0042bb09:
        test eax,eax
    L_0042bb0b:
        pop edi
    L_0042bb0c:
        je short L_0042bb1e
    L_0042bb0e:
        push eax
    L_0042bb0f:
        call asm_free_00452422
    L_0042bb14:
        add esp,4
    L_0042bb17:
        mov dword ptr [esi+34h],0
    L_0042bb1e:
        mov dword ptr [esi+34h],0
    L_0042bb25:
        ret
    }
}
