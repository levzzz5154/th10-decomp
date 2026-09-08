#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420B80..0x00420BFC: FUN_00420b80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420b80_00420b80() {
    __asm {
    L_00420b80:
        sub esp,104h
    L_00420b86:
        mov eax,dword ptr [data_00473660]
    L_00420b8b:
        xor eax,esp
    L_00420b8d:
        mov dword ptr [esp+100h],eax
    L_00420b94:
        mov eax,dword ptr [esp+108h]
    L_00420b9b:
        lea edx,[esp]
    L_00420b9e:
        sub edx,eax
    L_00420ba0:
        mov cl,byte ptr [eax]
    L_00420ba2:
        mov byte ptr [edx+eax],cl
    L_00420ba5:
        inc eax
    L_00420ba6:
        test cl,cl
    L_00420ba8:
        jne short L_00420ba0
    L_00420baa:
        lea eax,[esp]
    L_00420bad:
        push 2Eh
    L_00420baf:
        push eax
    L_00420bb0:
        call asm_strrchr_00452930
    L_00420bb5:
        mov ecx,dword ptr [data_0047783c]
    L_00420bbb:
        add esp,8
    L_00420bbe:
        mov byte ptr [eax+1],77h
    L_00420bc2:
        mov byte ptr [eax+2],61h
    L_00420bc6:
        mov byte ptr [eax+3],76h
    L_00420bca:
        push 0FFFFFFFFh
    L_00420bcc:
        push 2
    L_00420bce:
        lea edx,[esp+8]
    L_00420bd2:
        mov eax,492590h
    L_00420bd7:
        mov byte ptr [ecx+esi+1D892h],1
    L_00420bdf:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420be4:
        mov ecx,dword ptr [esp+100h]
    L_00420beb:
        xor ecx,esp
    L_00420bed:
        xor eax,eax
    L_00420bef:
        call asm_security_check_cookie_00458ea5
    L_00420bf4:
        add esp,104h
    L_00420bfa:
        ret 4
    }
}
