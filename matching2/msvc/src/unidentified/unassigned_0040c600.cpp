#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C600..0x0040C644: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c600() {
    __asm {
    L_0040c600:
        mov eax,dword ptr [eax+4]
    L_0040c603:
        mov edx,dword ptr [eax+4]
    L_0040c606:
        push esi
    L_0040c607:
        movzx esi,word ptr [edx+8]
    L_0040c60b:
        push edi
    L_0040c60c:
        mov edi,1
    L_0040c611:
        shl edi,cl
    L_0040c613:
        test esi,edi
    L_0040c615:
        je short L_0040c640
    L_0040c617:
        mov edx,dword ptr [edx+ecx*4+10h]
    L_0040c61b:
        test edx,edx
    L_0040c61d:
        jl short L_0040c62f
    L_0040c61f:
        lea ecx,[eax+8]
    L_0040c622:
        mov eax,dword ptr [ecx+1004h]
    L_0040c628:
        add eax,edx
    L_0040c62a:
        pop edi
    L_0040c62b:
        add eax,ecx
    L_0040c62d:
        pop esi
    L_0040c62e:
        ret
    L_0040c62f:
        mov eax,dword ptr [eax+1014h]
    L_0040c635:
        mov esi,dword ptr [eax]
    L_0040c637:
        push edx
    L_0040c638:
        mov ecx,eax
    L_0040c63a:
        call dword ptr [esi+8]
    L_0040c63d:
        pop edi
    L_0040c63e:
        pop esi
    L_0040c63f:
        ret
    L_0040c640:
        pop edi
    L_0040c641:
        xor eax,eax
    L_0040c643:
        pop esi
    L_0040c644:
        ret
    }
}
