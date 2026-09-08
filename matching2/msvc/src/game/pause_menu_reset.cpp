#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424D90..0x00424EA0: FUN_00424d90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424d90_00424d90() {
    __asm {
    L_00424d90:
        mov dword ptr [esi+458h],1
    L_00424d9a:
        mov eax,dword ptr [esi+470h]
    L_00424da0:
        push edi
    L_00424da1:
        xor edi,edi
    L_00424da3:
        test al,1
    L_00424da5:
        mov edx,0FFF0BDC1h
    L_00424daa:
        mov ecx,476F78h
    L_00424daf:
        jne short L_00424dd2
    L_00424db1:
        or eax,1
    L_00424db4:
        mov dword ptr [esi+464h],edi
    L_00424dba:
        mov dword ptr [esi+460h],edx
    L_00424dc0:
        mov dword ptr [esi+468h],edi
    L_00424dc6:
        mov dword ptr [esi+46Ch],ecx
    L_00424dcc:
        mov dword ptr [esi+470h],eax
    L_00424dd2:
        mov dword ptr [esi+464h],0FFFFFFFFh
    L_00424ddc:
        mov dword ptr [esi+468h],0BF800000h
    L_00424de6:
        mov dword ptr [esi+460h],0FFFFFFFEh
    L_00424df0:
        mov eax,dword ptr [esi+484h]
    L_00424df6:
        test al,1
    L_00424df8:
        jne short L_00424e1b
    L_00424dfa:
        or eax,1
    L_00424dfd:
        mov dword ptr [esi+478h],edi
    L_00424e03:
        mov dword ptr [esi+474h],edx
    L_00424e09:
        mov dword ptr [esi+47Ch],edi
    L_00424e0f:
        mov dword ptr [esi+480h],ecx
    L_00424e15:
        mov dword ptr [esi+484h],eax
    L_00424e1b:
        mov dword ptr [esi+478h],edi
    L_00424e21:
        mov dword ptr [esi+47Ch],edi
    L_00424e27:
        mov dword ptr [esi+474h],0FFFFFFFFh
    L_00424e31:
        mov eax,dword ptr [esi+498h]
    L_00424e37:
        test al,1
    L_00424e39:
        jne short L_00424e5c
    L_00424e3b:
        or eax,1
    L_00424e3e:
        mov dword ptr [esi+48Ch],edi
    L_00424e44:
        mov dword ptr [esi+488h],edx
    L_00424e4a:
        mov dword ptr [esi+490h],edi
    L_00424e50:
        mov dword ptr [esi+494h],ecx
    L_00424e56:
        mov dword ptr [esi+498h],eax
    L_00424e5c:
        mov edx,dword ptr [data_00491c10]
    L_00424e62:
        mov dword ptr [esi+48Ch],edi
    L_00424e68:
        mov dword ptr [esi+490h],edi
    L_00424e6e:
        mov dword ptr [esi+488h],0FFFFFFFFh
    L_00424e78:
        mov eax,dword ptr [esi+329Ch]
    L_00424e7e:
        push eax
    L_00424e7f:
        call asm_AnimationManager_SetFlag_004492a0
    L_00424e84:
        mov eax,dword ptr [data_0047770c]
    L_00424e89:
        mov dword ptr [esi+329Ch],edi
    L_00424e8f:
        mov dword ptr [esi+329Ch],edi
    L_00424e95:
        mov ecx,dword ptr [data_00474c70]
    L_00424e9b:
        pop edi
    L_00424e9c:
        jmp asm_Animation_SetActiveCount_00413790
    }
}
