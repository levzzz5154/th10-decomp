#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004601A1..0x004601E7: FUN_004601a1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004601a1_004601a1() {
    __asm {
    L_004601a1:
        push ebp
    L_004601a2:
        mov ebp,esp
    L_004601a4:
        sub esp,0Ch
    L_004601a7:
        mov eax,dword ptr [data_00473660]
    L_004601ac:
        xor eax,ebp
    L_004601ae:
        push 6
    L_004601b0:
        mov dword ptr [ebp-4],eax
    L_004601b3:
        lea eax,[ebp-0Ch]
    L_004601b6:
        push eax
    L_004601b7:
        push 1004h
    L_004601bc:
        push dword ptr [ebp+8]
    L_004601bf:
        mov byte ptr [ebp-6],0
    L_004601c3:
        call dword ptr [data_0046605c]
    L_004601c9:
        test eax,eax
    L_004601cb:
        jne short L_004601d2
    L_004601cd:
        or eax,0FFFFFFFFh
    L_004601d0:
        jmp short L_004601dc
    L_004601d2:
        lea eax,[ebp-0Ch]
    L_004601d5:
        push eax
    L_004601d6:
        call asm_atol_004527ee
    L_004601db:
        pop ecx
    L_004601dc:
        mov ecx,dword ptr [ebp-4]
    L_004601df:
        xor ecx,ebp
    L_004601e1:
        call asm_security_check_cookie_00458ea5
    L_004601e6:
        leave
    L_004601e7:
        ret
    }
}
