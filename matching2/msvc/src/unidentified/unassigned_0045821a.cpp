#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045821A..0x0045825A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045821a() {
    __asm {
    L_0045821a:
        xor eax,eax
    L_0045821c:
        inc eax
    L_0045821d:
        ret
    L_0045821e:
        mov esp,dword ptr [ebp-18h]
    L_00458221:
        call asm_resetstkoflw_00458d91
    L_00458226:
        push 20h
    L_00458228:
        call asm_malloc_00452706
    L_0045822d:
        pop ecx
    L_0045822e:
        mov dword ptr [ebp-1C8h],eax
    L_00458234:
        test eax,eax
    L_00458236:
        jne short L_00458241
    L_00458238:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045823c:
        jmp asm_target_0045885e
    L_00458241:
        mov dword ptr [ebp-1E4h],1
    L_0045824b:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045824f:
        mov edi,dword ptr [ebp-1E0h]
    L_00458255:
        mov ebx,dword ptr [ebp-1C8h]
    }
}
