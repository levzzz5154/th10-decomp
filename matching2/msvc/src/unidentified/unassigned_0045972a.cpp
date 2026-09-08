#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045972A..0x00459775: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045972a() {
    __asm {
    L_0045972a:
        push esi
    L_0045972b:
        push edi
    L_0045972c:
        mov esi,499200h
    L_00459731:
        mov edi,dword ptr [esi]
    L_00459733:
        test edi,edi
    L_00459735:
        je short L_00459768
    L_00459737:
        lea eax,[edi+480h]
    L_0045973d:
        jmp short L_00459759
    L_0045973f:
        cmp dword ptr [edi+8],0
    L_00459743:
        je short L_0045974f
    L_00459745:
        lea eax,[edi+0Ch]
    L_00459748:
        push eax
    L_00459749:
        call dword ptr [data_004660bc]
    L_0045974f:
        mov eax,dword ptr [esi]
    L_00459751:
        add edi,24h
    L_00459754:
        add eax,480h
    L_00459759:
        cmp edi,eax
    L_0045975b:
        jb short L_0045973f
    L_0045975d:
        push dword ptr [esi]
    L_0045975f:
        call asm_free_00452422
    L_00459764:
        and dword ptr [esi],0
    L_00459767:
        pop ecx
    L_00459768:
        add esi,4
    L_0045976b:
        cmp esi,499300h
    L_00459771:
        jl short L_00459731
    L_00459773:
        pop edi
    L_00459774:
        pop esi
    L_00459775:
        ret
    }
}
