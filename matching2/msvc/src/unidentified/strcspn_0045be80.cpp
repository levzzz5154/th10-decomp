#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BE80..0x0045BEC5: _strcspn
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strcspn_0045be80() {
    __asm {
    L_0045be80:
        push ebp
    L_0045be81:
        mov ebp,esp
    L_0045be83:
        push esi
    L_0045be84:
        xor eax,eax
    L_0045be86:
        push eax
    L_0045be87:
        push eax
    L_0045be88:
        push eax
    L_0045be89:
        push eax
    L_0045be8a:
        push eax
    L_0045be8b:
        push eax
    L_0045be8c:
        push eax
    L_0045be8d:
        push eax
    L_0045be8e:
        mov edx,dword ptr [ebp+0Ch]
    L_0045be91:
        TH10_NOP_LEA_ECX_DISP8()
    L_0045be94:
        mov al,byte ptr [edx]
    L_0045be96:
        or al,al
    L_0045be98:
        je short L_0045bea3
    L_0045be9a:
        add edx,1
    L_0045be9d:
        bts dword ptr [esp],eax
    L_0045bea1:
        jmp short L_0045be94
    L_0045bea3:
        mov esi,dword ptr [ebp+8]
    L_0045bea6:
        or ecx,0FFFFFFFFh
    L_0045bea9:
        TH10_NOP_LEA_ECX_DISP8()
    L_0045beac:
        add ecx,1
    L_0045beaf:
        mov al,byte ptr [esi]
    L_0045beb1:
        or al,al
    L_0045beb3:
        je short L_0045bebe
    L_0045beb5:
        add esi,1
    L_0045beb8:
        bt dword ptr [esp],eax
    L_0045bebc:
        jae short L_0045beac
    L_0045bebe:
        mov eax,ecx
    L_0045bec0:
        add esp,20h
    L_0045bec3:
        pop esi
    L_0045bec4:
        leave
    L_0045bec5:
        ret
    }
}
