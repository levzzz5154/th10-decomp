#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452930..0x0045295C: _strrchr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strrchr_00452930() {
    __asm {
    L_00452930:
        push ebp
    L_00452931:
        mov ebp,esp
    L_00452933:
        push edi
    L_00452934:
        mov edi,dword ptr [ebp+8]
    L_00452937:
        xor eax,eax
    L_00452939:
        or ecx,0FFFFFFFFh
    L_0045293c:
        repne scasb
    L_0045293e:
        add ecx,1
    L_00452941:
        neg ecx
    L_00452943:
        sub edi,1
    L_00452946:
        mov al,byte ptr [ebp+0Ch]
    L_00452949:
        std
    L_0045294a:
        repne scasb
    L_0045294c:
        add edi,1
    L_0045294f:
        cmp byte ptr [edi],al
    L_00452951:
        je short L_00452957
    L_00452953:
        xor eax,eax
    L_00452955:
        jmp short L_00452959
    L_00452957:
        mov eax,edi
    L_00452959:
        cld
    L_0045295a:
        pop edi
    L_0045295b:
        leave
    L_0045295c:
        ret
    }
}
