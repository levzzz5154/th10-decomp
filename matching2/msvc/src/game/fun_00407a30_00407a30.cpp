#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.

// 0x00407A30..0x00407BDE: FUN_00407a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407a30_00407a30() {
    __asm {
    L_00407a30:
        push ecx
    L_00407a31:
        mov eax,dword ptr [esi+6D8h]
    L_00407a37:
        cmp dword ptr [esi+6B4h],eax
    L_00407a3d:
        mov dword ptr [esp],eax
    L_00407a40:
        jl asm_target_00407b4b
    L_00407a46:
        push ebx
    L_00407a47:
        push edi
    L_00407a48:
        mov edi,dword ptr [esi+458h]
    L_00407a4e:
        xor ebx,ebx
    L_00407a50:
        cmp edi,ebx
    L_00407a52:
        jl short L_00407a5f
    L_00407a54:
        push ebx
    L_00407a55:
        mov ecx,492590h
    L_00407a5a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407a5f:
        mov edx,dword ptr [esi+6E0h]
    L_00407a65:
        mov ecx,dword ptr [esi+6DCh]
    L_00407a6b:
        inc edx
    L_00407a6c:
        mov eax,edx
    L_00407a6e:
        cmp eax,ecx
    L_00407a70:
        mov dword ptr [esi+6E0h],edx
    L_00407a76:
        jl short L_00407a82
    L_00407a78:
        and dword ptr [esi+43Ch],0FFFFFF7Fh
    L_00407a82:
        mov eax,dword ptr [data_00477834]
    L_00407a87:
        fld dword ptr [eax+3C0h]
    L_00407a8d:
        fsub dword ptr [esi+3B4h]
    L_00407a93:
        fld dword ptr [eax+3C4h]
    L_00407a99:
        fsub dword ptr [esi+3B8h]
    L_00407a9f:
        fld dword ptr [data_00470b04]
    L_00407aa5:
        fld st(1)
    L_00407aa7:
        fucompp
    L_00407aa9:
        fnstsw ax
    L_00407aab:
        test ah,44h
    L_00407aae:
        jp short L_00407acf
    L_00407ab0:
        fld dword ptr [data_00470b04]
    L_00407ab6:
        fld st(2)
    L_00407ab8:
        fucompp
    L_00407aba:
        fnstsw ax
    L_00407abc:
        test ah,44h
    L_00407abf:
        jp short L_00407acf
    L_00407ac1:
        fstp st(0)
    L_00407ac3:
        mov dword ptr [esp+8],3FC90FDBh
    L_00407acb:
        fstp st(0)
    L_00407acd:
        jmp short L_00407ad7
    L_00407acf:
        fxch
    L_00407ad1:
        fpatan
    L_00407ad3:
        fstp dword ptr [esp+8]
    L_00407ad7:
        mov eax,dword ptr [esi+6C8h]
    L_00407add:
        mov ecx,dword ptr [esp+8]
    L_00407ae1:
        push eax
    L_00407ae2:
        push ecx
    L_00407ae3:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407ae8:
        fstp dword ptr [esi+3E4h]
    L_00407aee:
        fld dword ptr [esi+6C4h]
    L_00407af4:
        fst dword ptr [esi+3D8h]
    L_00407afa:
        mov eax,dword ptr [esi+6C0h]
    L_00407b00:
        test al,1
    L_00407b02:
        fstp dword ptr [esp+8]
    L_00407b06:
        jne short L_00407b31
    L_00407b08:
        or eax,1
    L_00407b0b:
        mov dword ptr [esi+6B4h],ebx
    L_00407b11:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_00407b1b:
        mov dword ptr [esi+6B8h],ebx
    L_00407b21:
        mov dword ptr [esi+6BCh],476F78h
    L_00407b2b:
        mov dword ptr [esi+6C0h],eax
    L_00407b31:
        pop edi
    L_00407b32:
        mov dword ptr [esi+6B4h],ebx
    L_00407b38:
        mov dword ptr [esi+6B8h],ebx
    L_00407b3e:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_00407b48:
        pop ebx
    L_00407b49:
        jmp short L_00407b63
    L_00407b4b:
        fld dword ptr [esi+3D8h]
    L_00407b51:
        fld st(0)
    L_00407b53:
        fmul dword ptr [esi+6B8h]
    L_00407b59:
        fidiv dword ptr [esp]
    L_00407b5c:
        fsubr st,st(1)
    L_00407b5e:
        fstp dword ptr [esp]
    L_00407b61:
        fstp st(0)
    L_00407b63:
        mov edx,dword ptr [esp]
    L_00407b66:
        mov eax,dword ptr [esi+3E4h]
    L_00407b6c:
        push edx
    L_00407b6d:
        push eax
    L_00407b6e:
        lea ecx,[esi+3C0h]
    L_00407b74:
        call asm_Score_SetPolarVector_00408750
    L_00407b79:
        mov edx,dword ptr [esi+6B4h]
    L_00407b7f:
        mov ecx,dword ptr [esi+6BCh]
    L_00407b85:
        mov dword ptr [esi+6B0h],edx
    L_00407b8b:
        fld dword ptr [ecx]
    L_00407b8d:
        fcomp dword ptr [data_00470b68]
    L_00407b93:
        fnstsw ax
    L_00407b95:
        test ah,41h
    L_00407b98:
        jne short L_00407bc4
    L_00407b9a:
        fld dword ptr [ecx]
    L_00407b9c:
        fcomp dword ptr [data_00470b64]
    L_00407ba2:
        fnstsw ax
    L_00407ba4:
        test ah,5
    L_00407ba7:
        jp short L_00407bc4
    L_00407ba9:
        fld dword ptr [esi+6B8h]
    L_00407baf:
        inc edx
    L_00407bb0:
        fadd dword ptr [data_00470afc]
    L_00407bb6:
        mov dword ptr [esi+6B4h],edx
    L_00407bbc:
        fstp dword ptr [esi+6B8h]
    L_00407bc2:
        pop ecx
    L_00407bc3:
        ret
    L_00407bc4:
        fld dword ptr [esi+6B8h]
    L_00407bca:
        fadd dword ptr [ecx]
    L_00407bcc:
        fst dword ptr [esi+6B8h]
    L_00407bd2:
        call asm_FUN_00463b2c_00463b2c
    L_00407bd7:
        mov dword ptr [esi+6B4h],eax
    L_00407bdd:
        pop ecx
    L_00407bde:
        ret
    }
}
