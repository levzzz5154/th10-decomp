#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464B1C..0x00464BCD: FUN_00464b1c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464b1c_00464b1c() {
    __asm {
    L_00464b1c:
        push edx
    L_00464b1d:
        sub esp,30h
    L_00464b20:
        fstp tbyte ptr [esp+18h]
    L_00464b24:
        fstp tbyte ptr [esp]
    L_00464b27:
        xor edx,edx
    L_00464b29:
        mov eax,dword ptr [esp+6]
    L_00464b2d:
        test eax,7FFF0000h
    L_00464b32:
        je short L_00464b3e
    L_00464b34:
        call asm_FUN_00464916_00464916
    L_00464b39:
        add esp,30h
    L_00464b3c:
        pop edx
    L_00464b3d:
        ret
    L_00464b3e:
        fld tbyte ptr [esp]
    L_00464b41:
        fld tbyte ptr [esp+18h]
    L_00464b45:
        mov eax,dword ptr [esp]
    L_00464b48:
        or eax,dword ptr [esp+4]
    L_00464b4c:
        je short L_00464bc7
    L_00464b4e:
        fxch
    L_00464b50:
        fstp tbyte ptr [esp+0Ch]
    L_00464b54:
        fld tbyte ptr [esp]
    L_00464b57:
        fxch
    L_00464b59:
        or edx,2
    L_00464b5c:
        fnstcw word ptr [esp+24h]
    L_00464b60:
        mov eax,dword ptr [esp+24h]
    L_00464b64:
        or eax,33Fh
    L_00464b69:
        mov dword ptr [esp+28h],eax
    L_00464b6d:
        fldcw word ptr [esp+28h]
    L_00464b71:
        mov eax,dword ptr [esp+20h]
    L_00464b75:
        and eax,7FFFh
    L_00464b7a:
        cmp eax,7FBEh
    L_00464b7f:
        ja short L_00464b99
    L_00464b81:
        or edx,1
    L_00464b84:
        fmul qword ptr [data_004770d4]
    L_00464b8a:
        fstp tbyte ptr [esp+18h]
    L_00464b8e:
        fmul qword ptr [data_004770d4]
    L_00464b94:
        fstp tbyte ptr [esp]
    L_00464b97:
        jmp short L_00464bb9
    L_00464b99:
        fnstcw word ptr [esp+24h]
    L_00464b9d:
        mov eax,dword ptr [esp+24h]
    L_00464ba1:
        or eax,300h
    L_00464ba6:
        mov dword ptr [esp+28h],eax
    L_00464baa:
        fldcw word ptr [esp+28h]
    L_00464bae:
        fstp st(0)
    L_00464bb0:
        fmul qword ptr [data_004770d4]
    L_00464bb6:
        fstp tbyte ptr [esp]
    L_00464bb9:
        fldcw word ptr [esp+24h]
    L_00464bbd:
        call asm_FUN_00464916_00464916
    L_00464bc2:
        add esp,30h
    L_00464bc5:
        pop edx
    L_00464bc6:
        ret
    L_00464bc7:
        fprem
    L_00464bc9:
        add esp,30h
    L_00464bcc:
        pop edx
    L_00464bcd:
        ret
    }
}
