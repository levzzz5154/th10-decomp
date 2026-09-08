#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A0C0..0x0044A128: FUN_0044a0c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044a0c0_0044a0c0() {
    __asm {
    L_0044a0c0:
        sub esp,34h
    L_0044a0c3:
        push esi
    L_0044a0c4:
        mov esi,dword ptr [data_00466280]
    L_0044a0ca:
        lea eax,[esp+4]
    L_0044a0ce:
        push eax
    L_0044a0cf:
        push 0
    L_0044a0d1:
        mov dword ptr [esp+0Ch],34h
    L_0044a0d9:
        mov dword ptr [esp+10h],0FFh
    L_0044a0e1:
        call esi
    L_0044a0e3:
        test eax,eax
    L_0044a0e5:
        je short L_0044a10f
    L_0044a0e7:
        lea ecx,[esp+4]
    L_0044a0eb:
        push ecx
    L_0044a0ec:
        push 1
    L_0044a0ee:
        call esi
    L_0044a0f0:
        test eax,eax
    L_0044a0f2:
        je short L_0044a10f
    L_0044a0f4:
        push 470580h
    L_0044a0f9:
        mov ecx,474F70h
    L_0044a0fe:
        call asm_TextLog_Append_0044b810
    L_0044a103:
        add esp,4
    L_0044a106:
        mov ax,1
    L_0044a10a:
        pop esi
    L_0044a10b:
        add esp,34h
    L_0044a10e:
        ret
    L_0044a10f:
        push 194h
    L_0044a114:
        push 4918B8h
    L_0044a119:
        push 0
    L_0044a11b:
        call dword ptr [data_0046627c]
    L_0044a121:
        xor ax,ax
    L_0044a124:
        pop esi
    L_0044a125:
        add esp,34h
    L_0044a128:
        ret
    }
}
