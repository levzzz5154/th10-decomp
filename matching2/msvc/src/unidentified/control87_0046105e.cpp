#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046105E..0x0046108F: __control87
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_control87_0046105e() {
    __asm {
    L_0046105e:
        push ebp
    L_0046105f:
        mov ebp,esp
    L_00461061:
        push ecx
    L_00461062:
        push ebx
    L_00461063:
        wait
        fnstcw word ptr [ebp-4]
    L_00461067:
        mov ebx,dword ptr [ebp-4]
    L_0046106a:
        call asm_abstract_cw_00460ee4
    L_0046106f:
        mov ebx,eax
    L_00461071:
        mov eax,dword ptr [ebp+0Ch]
    L_00461074:
        not eax
    L_00461076:
        and ebx,eax
    L_00461078:
        mov eax,dword ptr [ebp+8]
    L_0046107b:
        and eax,dword ptr [ebp+0Ch]
    L_0046107e:
        or ebx,eax
    L_00461080:
        call asm_hw_cw_00460f76
    L_00461085:
        mov dword ptr [ebp+0Ch],eax
    L_00461088:
        fldcw word ptr [ebp+0Ch]
    L_0046108b:
        mov eax,ebx
    L_0046108d:
        pop ebx
    L_0046108e:
        leave
    L_0046108f:
        ret
    }
}
