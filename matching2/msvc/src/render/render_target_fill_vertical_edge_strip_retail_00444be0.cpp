#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444B10..0x00444BD8: FUN_00444b10
// Naked body preserves the retail register/stack ABI.

// 0x00444BE0..0x00444CA8: RenderTarget_FillVerticalEdgeStripRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RenderTarget_FillVerticalEdgeStripRetail_00444be0() {
    __asm {
    L_00444be0:
        sub esp,8
    L_00444be3:
        push esi
    L_00444be4:
        mov esi,eax
    L_00444be6:
        cmp esi,3
    L_00444be9:
        jge short L_00444bf3
    L_00444beb:
        or eax,0FFFFFFFFh
    L_00444bee:
        pop esi
    L_00444bef:
        add esp,8
    L_00444bf2:
        ret
    L_00444bf3:
        mov eax,dword ptr [ecx+394h]
    L_00444bf9:
        fld dword ptr [ecx+58h]
    L_00444bfc:
        fadd dword ptr [eax+2Ch]
    L_00444bff:
        push edi
    L_00444c00:
        fld dword ptr [eax+20h]
    L_00444c03:
        mov edi,3F800000h
    L_00444c08:
        fadd dword ptr [ecx+54h]
    L_00444c0b:
        fstp dword ptr [esp+8]
    L_00444c0f:
        fld dword ptr [eax+2Ch]
    L_00444c12:
        fsub dword ptr [eax+24h]
    L_00444c15:
        lea eax,[esi+1]
    L_00444c18:
        cdq
    L_00444c19:
        sub eax,edx
    L_00444c1b:
        sar eax,1
    L_00444c1d:
        dec eax
    L_00444c1e:
        test esi,esi
    L_00444c20:
        mov dword ptr [esp+0Ch],eax
    L_00444c24:
        fidiv dword ptr [esp+0Ch]
    L_00444c28:
        fstp dword ptr [esp+0Ch]
    L_00444c2c:
        fld st(0)
    L_00444c2e:
        jle short L_00444c60
    L_00444c30:
        lea edx,[esi-1]
    L_00444c33:
        shr edx,1
    L_00444c35:
        lea eax,[ebx+14h]
    L_00444c38:
        inc edx
    L_00444c39:
        push ebp
    L_00444c3a:
        lea ebx,[ebx+force_disp32_zero]
    L_00444c40:
        mov ebp,dword ptr [esp+0Ch]
    L_00444c44:
        fst dword ptr [eax+4]
    L_00444c47:
        fsub dword ptr [esp+10h]
    L_00444c4b:
        mov dword ptr [eax],ebp
    L_00444c4d:
        mov ebp,dword ptr [ecx+2FCh]
    L_00444c53:
        mov dword ptr [eax-4],ebp
    L_00444c56:
        mov dword ptr [eax-8],edi
    L_00444c59:
        add eax,38h
    L_00444c5c:
        dec edx
    L_00444c5d:
        jne short L_00444c40
    L_00444c5f:
        pop ebp
    L_00444c60:
        cmp esi,1
    L_00444c63:
        fstp st(0)
    L_00444c65:
        mov eax,dword ptr [ecx+394h]
    L_00444c6b:
        fld dword ptr [eax+28h]
    L_00444c6e:
        fadd dword ptr [ecx+54h]
    L_00444c71:
        fstp dword ptr [esp+8]
    L_00444c75:
        jle short L_00444c9f
    L_00444c77:
        lea edx,[esi-2]
    L_00444c7a:
        shr edx,1
    L_00444c7c:
        lea eax,[ebx+30h]
    L_00444c7f:
        inc edx
    L_00444c80:
        mov esi,dword ptr [esp+8]
    L_00444c84:
        fst dword ptr [eax+4]
    L_00444c87:
        fsub dword ptr [esp+0Ch]
    L_00444c8b:
        mov dword ptr [eax],esi
    L_00444c8d:
        mov esi,dword ptr [ecx+2FCh]
    L_00444c93:
        mov dword ptr [eax-4],esi
    L_00444c96:
        mov dword ptr [eax-8],edi
    L_00444c99:
        add eax,38h
    L_00444c9c:
        dec edx
    L_00444c9d:
        jne short L_00444c80
    L_00444c9f:
        pop edi
    L_00444ca0:
        fstp st(0)
    L_00444ca2:
        xor eax,eax
    L_00444ca4:
        pop esi
    L_00444ca5:
        add esp,8
    L_00444ca8:
        ret
    }
}
