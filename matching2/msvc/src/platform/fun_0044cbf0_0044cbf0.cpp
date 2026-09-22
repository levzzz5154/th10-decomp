#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3403): closest_byte_count=651/651; first_diff=none
// residual_class=COM_streamer_constructor_SEH_frame_vtable_layout_and_private
// argument homes; live Ghidra decompile resolves the DirectSound notification
// flow, allocation cleanup, and 0x0044D6A0 handoff, but no production-valid
// readable interface layout reproduced the retail frame.
// variants_tested=live Ghidra decompile plus callers/callees and native-LTCG
// feasibility analysis around 0x0043D950, 0x0044D6A0, operator_new, and the
// DirectSound vtable slots. next_lever=restore the concrete COM interface
// declarations and exception-state ownership, then test a real native-LTCG
// constructor cluster without changing the fixed ABI or SEH scope.
// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.

// 0x0044CBF0..0x0044CE7A: FUN_0044cbf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044cbf0_0044cbf0() {
    __asm {
    L_0044cbf0:
        push 0FFFFFFFFh
    L_0044cbf2:
        push 46531Bh
    L_0044cbf7:
        mov eax,dword ptr fs:[0]
    L_0044cbfd:
        push eax
    L_0044cbfe:
        mov dword ptr fs:[0],esp
    L_0044cc05:
        sub esp,4Ch
    L_0044cc08:
        mov eax,dword ptr [data_00473660]
    L_0044cc0d:
        xor eax,esp
    L_0044cc0f:
        push ebx
    L_0044cc10:
        mov ebx,dword ptr [esp+64h]
    L_0044cc14:
        mov dword ptr [esp+10h],ecx
    L_0044cc18:
        mov ecx,dword ptr [esp+74h]
    L_0044cc1c:
        push ebp
    L_0044cc1d:
        mov ebp,dword ptr [esp+84h]
    L_0044cc24:
        push esi
    L_0044cc25:
        mov dword ptr [esp+48h],ecx
    L_0044cc29:
        mov ecx,dword ptr [esp+84h]
    L_0044cc30:
        mov esi,edx
    L_0044cc32:
        mov edx,dword ptr [esp+78h]
    L_0044cc36:
        mov dword ptr [esp+54h],eax
    L_0044cc3a:
        mov eax,dword ptr [esp+68h]
    L_0044cc3e:
        push edi
    L_0044cc3f:
        mov dword ptr [esp+54h],ecx
    L_0044cc43:
        mov ecx,dword ptr [eax]
    L_0044cc45:
        mov dword ptr [esp+48h],edx
    L_0044cc49:
        mov edx,dword ptr [esp+84h]
    L_0044cc50:
        xor edi,edi
    L_0044cc52:
        cmp ecx,edi
    L_0044cc54:
        mov dword ptr [esp+18h],eax
    L_0044cc58:
        mov dword ptr [esp+50h],edx
    L_0044cc5c:
        jne short L_0044cc68
    L_0044cc5e:
        mov eax,800401F0h
    L_0044cc63:
        jmp asm_target_0044ce5b
    L_0044cc68:
        push 94h
    L_0044cc6d:
        mov dword ptr [esp+18h],edi
    L_0044cc71:
        mov dword ptr [esp+14h],edi
    L_0044cc75:
        call asm_operator_new_00452493
    L_0044cc7a:
        add esp,4
    L_0044cc7d:
        cmp eax,edi
    L_0044cc7f:
        je short L_0044cc91
    L_0044cc81:
        mov dword ptr [eax+90h],edi
    L_0044cc87:
        mov dword ptr [eax],edi
    L_0044cc89:
        mov dword ptr [eax+2Ch],edi
    L_0044cc8c:
        mov dword ptr [eax+7Ch],edi
    L_0044cc8f:
        mov edi,eax
    L_0044cc91:
        mov edx,dword ptr [esp+78h]
    L_0044cc95:
        mov eax,dword ptr [esp+74h]
    L_0044cc99:
        mov dword ptr [edi+90h],edx
    L_0044cc9f:
        mov edx,dword ptr [esp+48h]
    L_0044cca3:
        mov dword ptr [edi+88h],eax
    L_0044cca9:
        mov eax,dword ptr [esp+4Ch]
    L_0044ccad:
        mov dword ptr [edi+80h],ebx
    L_0044ccb3:
        mov dword ptr [edi+84h],ebx
    L_0044ccb9:
        xor ecx,ecx
    L_0044ccbb:
        mov dword ptr [edi+7Ch],1
    L_0044ccc2:
        mov dword ptr [esp+24h],ecx
    L_0044ccc6:
        mov dword ptr [esp+28h],ecx
    L_0044ccca:
        mov dword ptr [esp+2Ch],ecx
    L_0044ccce:
        mov dword ptr [esp+30h],ecx
    L_0044ccd2:
        mov dword ptr [esp+34h],ecx
    L_0044ccd6:
        mov dword ptr [esp+38h],ecx
    L_0044ccda:
        mov dword ptr [esp+3Ch],ecx
    L_0044ccde:
        mov ebx,ebp
    L_0044cce0:
        imul ebx,dword ptr [esp+90h]
    L_0044cce8:
        mov dword ptr [esp+40h],ecx
    L_0044ccec:
        mov dword ptr [esp+44h],ecx
    L_0044ccf0:
        mov ecx,dword ptr [esp+50h]
    L_0044ccf4:
        mov dword ptr [esp+38h],edx
    L_0044ccf8:
        mov edx,dword ptr [esp+54h]
    L_0044ccfc:
        mov dword ptr [esp+40h],ecx
    L_0044cd00:
        mov ecx,dword ptr [esp+18h]
    L_0044cd04:
        mov dword ptr [esp+3Ch],eax
    L_0044cd08:
        mov dword ptr [esp+24h],24h
    L_0044cd10:
        or esi,18188h
    L_0044cd16:
        mov dword ptr [esp+28h],esi
    L_0044cd1a:
        mov dword ptr [esp+2Ch],ebx
    L_0044cd1e:
        mov dword ptr [esp+44h],edx
    L_0044cd22:
        mov eax,dword ptr [edi+90h]
    L_0044cd28:
        add eax,20h
    L_0044cd2b:
        mov dword ptr [esp+34h],eax
    L_0044cd2f:
        mov eax,dword ptr [ecx]
    L_0044cd31:
        mov edx,dword ptr [eax]
    L_0044cd33:
        push 0
    L_0044cd35:
        lea ecx,[esp+18h]
    L_0044cd39:
        push ecx
    L_0044cd3a:
        lea ecx,[esp+2Ch]
    L_0044cd3e:
        push ecx
    L_0044cd3f:
        push eax
    L_0044cd40:
        call dword ptr [edx+0Ch]
    L_0044cd43:
        test eax,eax
    L_0044cd45:
        jl asm_target_0044cdd9
    L_0044cd4b:
        mov eax,dword ptr [esp+14h]
    L_0044cd4f:
        mov edx,dword ptr [eax]
    L_0044cd51:
        lea ecx,[esp+10h]
    L_0044cd55:
        push ecx
    L_0044cd56:
        push 46743Ch
    L_0044cd5b:
        push eax
    L_0044cd5c:
        call dword ptr [edx]
    L_0044cd5e:
        test eax,eax
    L_0044cd60:
        jl short L_0044cdd9
    L_0044cd62:
        lea edx,[ebp*8]
    L_0044cd69:
        push edx
    L_0044cd6a:
        call asm_operator_new_00452493
    L_0044cd6f:
        mov esi,eax
    L_0044cd71:
        add esp,4
    L_0044cd74:
        test esi,esi
    L_0044cd76:
        jne short L_0044cd82
    L_0044cd78:
        mov eax,8007000Eh
    L_0044cd7d:
        jmp asm_target_0044ce5b
    L_0044cd82:
        xor eax,eax
    L_0044cd84:
        test ebp,ebp
    L_0044cd86:
        jbe short L_0044cdac
    L_0044cd88:
        mov ecx,dword ptr [esp+90h]
    L_0044cd8f:
        dec ecx
    L_0044cd90:
        mov edx,dword ptr [esp+94h]
    L_0044cd97:
        mov dword ptr [esi+eax*8+4],edx
    L_0044cd9b:
        mov edx,dword ptr [esp+90h]
    L_0044cda2:
        mov dword ptr [esi+eax*8],ecx
    L_0044cda5:
        inc eax
    L_0044cda6:
        add ecx,edx
    L_0044cda8:
        cmp eax,ebp
    L_0044cdaa:
        jb short L_0044cd90
    L_0044cdac:
        mov eax,dword ptr [esp+10h]
    L_0044cdb0:
        mov ecx,dword ptr [eax]
    L_0044cdb2:
        push esi
    L_0044cdb3:
        push ebp
    L_0044cdb4:
        push eax
    L_0044cdb5:
        call dword ptr [ecx+0Ch]
    L_0044cdb8:
        xor ebp,ebp
    L_0044cdba:
        cmp eax,ebp
    L_0044cdbc:
        mov eax,dword ptr [esp+10h]
    L_0044cdc0:
        jge short L_0044cde3
    L_0044cdc2:
        cmp eax,ebp
    L_0044cdc4:
        je short L_0044cdd0
    L_0044cdc6:
        mov edx,dword ptr [eax]
    L_0044cdc8:
        push eax
    L_0044cdc9:
        call dword ptr [edx+8]
    L_0044cdcc:
        mov dword ptr [esp+10h],ebp
    L_0044cdd0:
        push esi
    L_0044cdd1:
        call asm_free_004524a1
    L_0044cdd6:
        add esp,4
    L_0044cdd9:
        mov eax,80004005h
    L_0044cdde:
        jmp asm_target_0044ce5b
    L_0044cde3:
        cmp eax,ebp
    L_0044cde5:
        je short L_0044cdf1
    L_0044cde7:
        mov ecx,dword ptr [eax]
    L_0044cde9:
        push eax
    L_0044cdea:
        call dword ptr [ecx+8]
    L_0044cded:
        mov dword ptr [esp+10h],ebp
    L_0044cdf1:
        push esi
    L_0044cdf2:
        call asm_free_004524a1
    L_0044cdf7:
        push 78h
    L_0044cdf9:
        call asm_operator_new_00452493
    L_0044cdfe:
        add esp,8
    L_0044ce01:
        mov dword ptr [esp+20h],eax
    L_0044ce05:
        cmp eax,ebp
    L_0044ce07:
        mov dword ptr [esp+64h],ebp
    L_0044ce0b:
        je short L_0044ce25
    L_0044ce0d:
        mov edx,dword ptr [esp+90h]
    L_0044ce14:
        mov ecx,dword ptr [esp+14h]
    L_0044ce18:
        push edx
    L_0044ce19:
        push edi
    L_0044ce1a:
        push ebx
    L_0044ce1b:
        push ecx
    L_0044ce1c:
        mov esi,eax
    L_0044ce1e:
        call asm_Recovery_InitializeSingleInterface_0044d6a0
    L_0044ce23:
        jmp short L_0044ce27
    L_0044ce25:
        xor eax,eax
    L_0044ce27:
        mov edx,dword ptr [esp+1Ch]
    L_0044ce2b:
        mov dword ptr [edx],eax
    L_0044ce2d:
        lea edi,[eax+34h]
    L_0044ce30:
        mov ecx,9
    L_0044ce35:
        lea esi,[esp+24h]
    L_0044ce39:
        rep movsd
    L_0044ce3b:
        mov eax,dword ptr [edx]
    L_0044ce3d:
        mov ecx,dword ptr [esp+18h]
    L_0044ce41:
        mov dword ptr [eax+58h],ecx
    L_0044ce44:
        mov eax,dword ptr [edx]
    L_0044ce46:
        mov ecx,dword ptr [esp+94h]
    L_0044ce4d:
        mov dword ptr [eax+70h],ecx
    L_0044ce50:
        mov edx,dword ptr [edx]
    L_0044ce52:
        mov dword ptr [edx+74h],0
    L_0044ce59:
        xor eax,eax
    L_0044ce5b:
        mov ecx,dword ptr [esp+5Ch]
    L_0044ce5f:
        pop edi
    L_0044ce60:
        pop esi
    L_0044ce61:
        pop ebp
    L_0044ce62:
        mov dword ptr fs:[0],ecx
    L_0044ce69:
        mov ecx,dword ptr [esp+4Ch]
    L_0044ce6d:
        pop ebx
    L_0044ce6e:
        xor ecx,esp
    L_0044ce70:
        call asm_security_check_cookie_00458ea5
    L_0044ce75:
        add esp,58h
    L_0044ce78:
        ret 2Ch
    }
}
