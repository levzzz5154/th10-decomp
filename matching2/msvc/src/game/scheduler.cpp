#include "asm_encoding.hpp"
#include "asm_symbols.hpp"






// 0x00449C00..0x00449C27: FUN_00449c00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449c00_00449c00() {
    __asm {
    L_00449c00:
        sub esp,8
    L_00449c03:
        push ebx
    L_00449c04:
        mov ebx,dword ptr [data_004660b0]
    L_00449c0a:
        push ebp
    L_00449c0b:
        push esi
    L_00449c0c:
        push edi
    L_00449c0d:
        push 492274h
    L_00449c12:
        call ebx
    L_00449c14:
        mov al,byte ptr [data_0049231c]
    L_00449c19:
        mov ebp,dword ptr [data_004660b4]
    L_00449c1f:
        inc al
    L_00449c21:
        mov byte ptr [data_0049231c],al
    L_00449c26:
        TH10_REL8(0xeb, 0x00449c26, VA_asm_FUN_00449c00_part_00449c30)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_00449c30:
        mov eax,dword ptr [esp+1Ch]
    L_00449c34:
        mov eax,dword ptr [eax+18h]
    L_00449c37:
        mov dword ptr [esp+10h],0
    L_00449c3f:
        nop
    L_00449c40:
        test eax,eax
    L_00449c42:
        je asm_target_00449cf0
    L_00449c48:
        mov ecx,dword ptr [eax+4]
    L_00449c4b:
        mov esi,dword ptr [eax]
    L_00449c4d:
        mov eax,dword ptr [esi+8]
    L_00449c50:
        test eax,eax
    L_00449c52:
        mov dword ptr [esp+14h],ecx
    L_00449c56:
        je short L_00449ccb
    L_00449c58:
        test byte ptr [esi+4],2
    L_00449c5c:
        je short L_00449cc7
    L_00449c5e:
        mov edi,edi
    L_00449c60:
        push 492274h
    L_00449c65:
        call ebp
    L_00449c67:
        dec byte ptr [data_0049231c]
    L_00449c6d:
        mov ecx,dword ptr [esi+20h]
    L_00449c70:
        call dword ptr [esi+8]
    L_00449c73:
        push 492274h
    L_00449c78:
        mov edi,eax
    L_00449c7a:
        call ebx
    L_00449c7c:
        mov cl,byte ptr [data_0049231c]
    L_00449c82:
        inc cl
    L_00449c84:
        cmp edi,7
    L_00449c87:
        mov byte ptr [data_0049231c],cl
    L_00449c8d:
        ja short L_00449cc7
    L_00449c8f:
        jmp dword ptr [edi*4+449D14h]
    L_00449c96:
        test byte ptr [esi+4],2
    L_00449c9a:
        jne short L_00449c60
    L_00449c9c:
        inc dword ptr [esp+10h]
    L_00449ca0:
        mov eax,dword ptr [esp+14h]
    L_00449ca4:
        jmp short L_00449c40
    L_00449ca6:
        mov edx,dword ptr [esp+1Ch]
    L_00449caa:
        mov ecx,esi
    L_00449cac:
        call asm_Scheduler_Remove_00449f60
    L_00449cb1:
        inc dword ptr [esp+10h]
    L_00449cb5:
        mov eax,dword ptr [esp+14h]
    L_00449cb9:
        jmp short L_00449c40
    L_00449cbb:
        mov eax,dword ptr [esi+10h]
    L_00449cbe:
        test eax,eax
    L_00449cc0:
        je short L_00449cc7
    L_00449cc2:
        mov ecx,dword ptr [esi+20h]
    L_00449cc5:
        call eax
    L_00449cc7:
        inc dword ptr [esp+10h]
    L_00449ccb:
        mov eax,dword ptr [esp+14h]
    L_00449ccf:
        jmp asm_target_00449c40
    L_00449cd4:
        mov dword ptr [esp+10h],0
    L_00449cdc:
        jmp short L_00449cf0
    L_00449cde:
        mov dword ptr [esp+10h],1
    L_00449ce6:
        jmp short L_00449cf0
    L_00449ce8:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00449cf0:
        push 492274h
    L_00449cf5:
        call ebp
    L_00449cf7:
        mov al,byte ptr [data_0049231c]
    L_00449cfc:
        pop edi
    L_00449cfd:
        pop esi
    L_00449cfe:
        dec al
    L_00449d00:
        pop ebp
    L_00449d01:
        mov byte ptr [data_0049231c],al
    L_00449d06:
        mov eax,dword ptr [esp+4]
    L_00449d0a:
        pop ebx
    L_00449d0b:
        add esp,8
    L_00449d0e:
        ret 4
    }
}

// 0x00449D40..0x00449E30: FUN_00449d40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449d40_00449d40() {
    __asm {
    L_00449d40:
        sub esp,8
    L_00449d43:
        push ebx
    L_00449d44:
        push ebp
    L_00449d45:
        mov ebp,dword ptr [data_004660b0]
    L_00449d4b:
        push 492274h
    L_00449d50:
        call ebp
    L_00449d52:
        mov dl,byte ptr [data_0049231c]
    L_00449d58:
        mov eax,dword ptr [esp+14h]
    L_00449d5c:
        mov ebx,dword ptr [data_004660b4]
    L_00449d62:
        inc dl
    L_00449d64:
        mov byte ptr [data_0049231c],dl
    L_00449d6a:
        mov eax,dword ptr [eax+3Ch]
    L_00449d6d:
        test eax,eax
    L_00449d6f:
        mov dword ptr [esp+8],0
    L_00449d77:
        je asm_target_00449e12
    L_00449d7d:
        push esi
    L_00449d7e:
        push edi
    L_00449d7f:
        nop
    L_00449d80:
        mov ecx,dword ptr [eax+4]
    L_00449d83:
        mov esi,dword ptr [eax]
    L_00449d85:
        mov eax,dword ptr [esi+8]
    L_00449d88:
        test eax,eax
    L_00449d8a:
        mov dword ptr [esp+14h],ecx
    L_00449d8e:
        je short L_00449dec
    L_00449d90:
        test byte ptr [esi+4],2
    L_00449d94:
        je short L_00449ddf
    L_00449d96:
        push 492274h
    L_00449d9b:
        call ebx
    L_00449d9d:
        dec byte ptr [data_0049231c]
    L_00449da3:
        mov ecx,dword ptr [esi+20h]
    L_00449da6:
        call dword ptr [esi+8]
    L_00449da9:
        push 492274h
    L_00449dae:
        mov edi,eax
    L_00449db0:
        call ebp
    L_00449db2:
        mov cl,byte ptr [data_0049231c]
    L_00449db8:
        inc cl
    L_00449dba:
        cmp edi,5
    L_00449dbd:
        mov byte ptr [data_0049231c],cl
    L_00449dc3:
        ja short L_00449ddf
    L_00449dc5:
        jmp dword ptr [edi*4+449E34h]
    L_00449dcc:
        test byte ptr [esi+4],2
    L_00449dd0:
        jne short L_00449d96
    L_00449dd2:
        jmp short L_00449ddf
    L_00449dd4:
        mov edx,dword ptr [esp+1Ch]
    L_00449dd8:
        mov ecx,esi
    L_00449dda:
        call asm_Scheduler_Remove_00449f60
    L_00449ddf:
        mov eax,dword ptr [esp+10h]
    L_00449de3:
        mov ecx,dword ptr [esp+14h]
    L_00449de7:
        inc eax
    L_00449de8:
        mov dword ptr [esp+10h],eax
    L_00449dec:
        test ecx,ecx
    L_00449dee:
        mov eax,ecx
    L_00449df0:
        jne short L_00449d80
    L_00449df2:
        jmp short L_00449e10
    L_00449df4:
        mov dword ptr [esp+10h],0
    L_00449dfc:
        jmp short L_00449e10
    L_00449dfe:
        mov dword ptr [esp+10h],1
    L_00449e06:
        jmp short L_00449e10
    L_00449e08:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00449e10:
        pop edi
    L_00449e11:
        pop esi
    L_00449e12:
        push 492274h
    L_00449e17:
        call ebx
    L_00449e19:
        mov al,byte ptr [data_0049231c]
    L_00449e1e:
        dec al
    L_00449e20:
        pop ebp
    L_00449e21:
        mov byte ptr [data_0049231c],al
    L_00449e26:
        mov eax,dword ptr [esp+4]
    L_00449e2a:
        pop ebx
    L_00449e2b:
        add esp,8
    L_00449e2e:
        ret 4
    }
}

// 0x00449ED0..0x00449F19: ?SchedulerCallback_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SchedulerCallback_Create_00449ed0() {
    __asm {
    L_00449ed0:
        push 24h
    L_00449ed2:
        call asm_operator_new_00452493
    L_00449ed7:
        xor ecx,ecx
    L_00449ed9:
        add esp,4
    L_00449edc:
        cmp eax,ecx
    L_00449ede:
        je short L_00449eff
    L_00449ee0:
        mov edx,dword ptr [eax+4]
    L_00449ee3:
        mov dword ptr [eax+8],ecx
    L_00449ee6:
        mov dword ptr [eax+0Ch],ecx
    L_00449ee9:
        mov dword ptr [eax+10h],ecx
    L_00449eec:
        mov dword ptr [eax],ecx
    L_00449eee:
        and edx,0FFFFFFFEh
    L_00449ef1:
        mov dword ptr [eax+4],edx
    L_00449ef4:
        mov dword ptr [eax+14h],eax
    L_00449ef7:
        mov dword ptr [eax+18h],ecx
    L_00449efa:
        mov dword ptr [eax+1Ch],ecx
    L_00449efd:
        jmp short L_00449f01
    L_00449eff:
        xor eax,eax
    L_00449f01:
        mov edx,dword ptr [esp+4]
    L_00449f05:
        mov dword ptr [eax+0Ch],ecx
    L_00449f08:
        mov dword ptr [eax+10h],ecx
    L_00449f0b:
        mov ecx,dword ptr [eax+4]
    L_00449f0e:
        or ecx,1
    L_00449f11:
        mov dword ptr [eax+8],edx
    L_00449f14:
        mov dword ptr [eax+4],ecx
    L_00449f17:
        ret 4
    }
}


