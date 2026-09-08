#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046271B..0x0046276C: _UnwindNestedFrames
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_UnwindNestedFrames_0046271b() {
    __asm {
    L_0046271b:
        push ebp
    L_0046271c:
        mov ebp,esp
    L_0046271e:
        push ecx
    L_0046271f:
        push ecx
    L_00462720:
        push ebx
    L_00462721:
        push esi
    L_00462722:
        push edi
    L_00462723:
        mov esi,dword ptr fs:[0]
    L_0046272a:
        mov dword ptr [ebp-4],esi
    L_0046272d:
        mov dword ptr [ebp-8],462744h
    L_00462734:
        push 0
    L_00462736:
        push dword ptr [ebp+0Ch]
    L_00462739:
        push dword ptr [ebp-8]
    L_0046273c:
        push dword ptr [ebp+8]
    L_0046273f:
        call asm_RtlUnwind_0046263a
    L_00462744:
        mov eax,dword ptr [ebp+0Ch]
    L_00462747:
        mov eax,dword ptr [eax+4]
    L_0046274a:
        and eax,0FFFFFFFDh
    L_0046274d:
        mov ecx,dword ptr [ebp+0Ch]
    L_00462750:
        mov dword ptr [ecx+4],eax
    L_00462753:
        mov edi,dword ptr fs:[0]
    L_0046275a:
        mov ebx,dword ptr [ebp-4]
    L_0046275d:
        mov dword ptr [ebx],edi
    L_0046275f:
        mov dword ptr fs:[0],ebx
    L_00462766:
        pop edi
    L_00462767:
        pop esi
    L_00462768:
        pop ebx
    L_00462769:
        leave
    L_0046276a:
        ret 8
    }
}
