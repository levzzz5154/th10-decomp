#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004526DA..0x00452705: __nh_malloc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_nh_malloc_004526da() {
    __asm {
    L_004526da:
        cmp dword ptr [esp+4],0FFFFFFE0h
    L_004526df:
        ja short L_00452703
    L_004526e1:
        push dword ptr [esp+4]
    L_004526e5:
        call asm_heap_alloc_0045265f
    L_004526ea:
        test eax,eax
    L_004526ec:
        pop ecx
    L_004526ed:
        jne short L_00452705
    L_004526ef:
        cmp dword ptr [esp+8],eax
    L_004526f3:
        je short L_00452705
    L_004526f5:
        push dword ptr [esp+4]
    L_004526f9:
        call asm_callnewh_00455737
    L_004526fe:
        test eax,eax
    L_00452700:
        pop ecx
    L_00452701:
        jne short L_004526e1
    L_00452703:
        xor eax,eax
    L_00452705:
        ret
    }
}
