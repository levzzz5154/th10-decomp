#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447EC0..0x00447F68: FUN_00447ec0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447ec0_00447ec0() {
    __asm {
    L_00447ec0:
        sub esp,10Ch
    L_00447ec6:
        mov eax,dword ptr [data_00473660]
    L_00447ecb:
        xor eax,esp
    L_00447ecd:
        push esi
    L_00447ece:
        push edi
    L_00447ecf:
        mov esi,ecx
    L_00447ed1:
        mov edi,edx
    L_00447ed3:
        mov dword ptr [esp+110h],eax
    L_00447eda:
        mov eax,dword ptr [edi+esi*4+3AD4E0h]
    L_00447ee1:
        test eax,eax
    L_00447ee3:
        je short L_00447eea
    L_00447ee5:
        call asm_AnimationManager_ClearIndexedResources_00447f70
    L_00447eea:
        push ebx
    L_00447eeb:
        lea eax,[esp+10h]
    L_00447eef:
        push 46E1C8h
    L_00447ef4:
        push eax
    L_00447ef5:
        call asm_sprintf_00452ae8
    L_00447efa:
        add esp,0Ch
    L_00447efd:
        push 0
    L_00447eff:
        lea ecx,[esp+0Ch]
    L_00447f03:
        push ecx
    L_00447f04:
        lea eax,[esp+14h]
    L_00447f08:
        call asm_FUN_0044b360_0044b360
    L_00447f0d:
        test eax,eax
    L_00447f0f:
        jne short L_00447f3e
    L_00447f11:
        push ebx
    L_00447f12:
        push 470150h
    L_00447f17:
        mov edi,474F70h
    L_00447f1c:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447f21:
        add esp,8
    L_00447f24:
        pop edi
    L_00447f25:
        or eax,0FFFFFFFFh
    L_00447f28:
        pop esi
    L_00447f29:
        mov ecx,dword ptr [esp+108h]
    L_00447f30:
        xor ecx,esp
    L_00447f32:
        call asm_security_check_cookie_00458ea5
    L_00447f37:
        add esp,10Ch
    L_00447f3d:
        ret
    L_00447f3e:
        mov edx,dword ptr [esp+8]
    L_00447f42:
        mov ecx,dword ptr [esp+110h]
    L_00447f49:
        mov dword ptr [edi+esi*4+3AD5E0h],eax
    L_00447f50:
        mov dword ptr [edi+esi*4+3AD660h],edx
    L_00447f57:
        pop edi
    L_00447f58:
        pop esi
    L_00447f59:
        xor ecx,esp
    L_00447f5b:
        xor eax,eax
    L_00447f5d:
        call asm_security_check_cookie_00458ea5
    L_00447f62:
        add esp,10Ch
    L_00447f68:
        ret
    }
}
