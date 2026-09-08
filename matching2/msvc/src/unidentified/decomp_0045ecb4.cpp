#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045ECB4..0x0045ED6F: __decomp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_decomp_0045ecb4() {
    __asm {
    L_0045ecb4:
        push ebp
    L_0045ecb5:
        mov ebp,esp
    L_0045ecb7:
        push ecx
    L_0045ecb8:
        push ecx
    L_0045ecb9:
        fld qword ptr [data_00470b70]
    L_0045ecbf:
        fld qword ptr [ebp+8]
    L_0045ecc2:
        fucompp
    L_0045ecc4:
        fnstsw ax
    L_0045ecc6:
        test ah,44h
    L_0045ecc9:
        jp short L_0045ecd4
    L_0045eccb:
        fldz
    L_0045eccd:
        xor edx,edx
    L_0045eccf:
        jmp asm_target_0045ed63
    L_0045ecd4:
        xor ecx,ecx
    L_0045ecd6:
        test word ptr [ebp+0Eh],7FF0h
    L_0045ecdc:
        jne short L_0045ed40
    L_0045ecde:
        test dword ptr [ebp+0Ch],0FFFFFh
    L_0045ece5:
        jne short L_0045ecec
    L_0045ece7:
        cmp dword ptr [ebp+8],ecx
    L_0045ecea:
        je short L_0045ed40
    L_0045ecec:
        fld qword ptr [ebp+8]
    L_0045ecef:
        mov edx,0FFFFFC03h
    L_0045ecf4:
        fcomp qword ptr [data_00470b70]
    L_0045ecfa:
        fnstsw ax
    L_0045ecfc:
        test ah,5
    L_0045ecff:
        jp short L_0045ed06
    L_0045ed01:
        xor eax,eax
    L_0045ed03:
        inc eax
    L_0045ed04:
        jmp short L_0045ed1b
    L_0045ed06:
        xor eax,eax
    L_0045ed08:
        jmp short L_0045ed1b
    L_0045ed0a:
        shl dword ptr [ebp+0Ch],1
    L_0045ed0d:
        test byte ptr [ebp+0Bh],80h
    L_0045ed11:
        je short L_0045ed17
    L_0045ed13:
        or dword ptr [ebp+0Ch],1
    L_0045ed17:
        shl dword ptr [ebp+8],1
    L_0045ed1a:
        dec edx
    L_0045ed1b:
        test byte ptr [ebp+0Eh],10h
    L_0045ed1f:
        je short L_0045ed0a
    L_0045ed21:
        and byte ptr [ebp+0Eh],0EFh
    L_0045ed25:
        cmp eax,ecx
    L_0045ed27:
        je short L_0045ed2d
    L_0045ed29:
        or byte ptr [ebp+0Fh],80h
    L_0045ed2d:
        fld qword ptr [ebp+8]
    L_0045ed30:
        push ecx
    L_0045ed31:
        push ecx
    L_0045ed32:
        push ecx
    L_0045ed33:
        fstp qword ptr [esp]
    L_0045ed36:
        call asm_set_exp_0045ebcb
    L_0045ed3b:
        add esp,0Ch
    L_0045ed3e:
        jmp short L_0045ed63
    L_0045ed40:
        fld qword ptr [ebp+8]
    L_0045ed43:
        push ecx
    L_0045ed44:
        push ecx
    L_0045ed45:
        push ecx
    L_0045ed46:
        fstp qword ptr [esp]
    L_0045ed49:
        call asm_set_exp_0045ebcb
    L_0045ed4e:
        mov edx,dword ptr [ebp+0Eh]
    L_0045ed51:
        shr edx,4
    L_0045ed54:
        and edx,7FFh
    L_0045ed5a:
        add esp,0Ch
    L_0045ed5d:
        sub edx,3FEh
    L_0045ed63:
        mov eax,dword ptr [ebp+10h]
    L_0045ed66:
        fstp qword ptr [ebp-8]
    L_0045ed69:
        fld qword ptr [ebp-8]
    L_0045ed6c:
        mov dword ptr [eax],edx
    L_0045ed6e:
        leave
    L_0045ed6f:
        ret
    }
}
