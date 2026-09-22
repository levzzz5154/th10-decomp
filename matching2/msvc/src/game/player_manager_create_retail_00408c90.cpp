// BLOCKED (D3804): closest_byte_count=1/136; first_diff=0x00408C90;
// residual_class=compiler-generated SEH registration/unregistration and
// private constructor/destructor ABIs across the 0x37B0-byte PlayerManager
// layout. variants_tested=live Ghidra decompile for 0x00408C90 and caller
// 0x00417870 (including 0x00408910, 0x004089C0, 0x00408AF0), plus an MSVC
// 13.10 standalone readable factory candidate (67-byte extent, 1/136
// comparable bytes); the exact assembly baseline was restored. next_lever=
// schema2 native-LTCG cluster rooted at real caller 0x00417870, with this
// factory, PlayerManager constructor/initializer/destructor, operator_new/free,
// and production manager layout/EH bindings co-compiled.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x00408C90..0x00408D17: PlayerManager_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PlayerManager_CreateRetail_00408c90() {
    __asm {
    L_00408c90:
        push 0FFFFFFFFh
    L_00408c92:
        push 46586Bh
    L_00408c97:
        mov eax,dword ptr fs:[0]
    L_00408c9d:
        push eax
    L_00408c9e:
        mov dword ptr fs:[0],esp
    L_00408ca5:
        push ecx
    L_00408ca6:
        push ebx
    L_00408ca7:
        push 37B0h
    L_00408cac:
        call asm_operator_new_00452493
    L_00408cb1:
        add esp,4
    L_00408cb4:
        mov dword ptr [esp+4],eax
    L_00408cb8:
        test eax,eax
    L_00408cba:
        mov dword ptr [esp+10h],0
    L_00408cc2:
        je short L_00408cce
    L_00408cc4:
        push eax
    L_00408cc5:
        call asm_PlayerManager_ConstructRetail_00408910
    L_00408cca:
        mov ebx,eax
    L_00408ccc:
        jmp short L_00408cd0
    L_00408cce:
        xor ebx,ebx
    L_00408cd0:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00408cd8:
        call asm_FUN_004089c0_004089c0
    L_00408cdd:
        test eax,eax
    L_00408cdf:
        je short L_00408d06
    L_00408ce1:
        test ebx,ebx
    L_00408ce3:
        je short L_00408cf4
    L_00408ce5:
        push ebx
    L_00408ce6:
        call asm_FUN_00408af0_00408af0
    L_00408ceb:
        push ebx
    L_00408cec:
        call asm_free_004524a1
    L_00408cf1:
        add esp,4
    L_00408cf4:
        xor eax,eax
    L_00408cf6:
        pop ebx
    L_00408cf7:
        mov ecx,dword ptr [esp+4]
    L_00408cfb:
        mov dword ptr fs:[0],ecx
    L_00408d02:
        add esp,10h
    L_00408d05:
        ret
    L_00408d06:
        mov ecx,dword ptr [esp+8]
    L_00408d0a:
        mov eax,ebx
    L_00408d0c:
        pop ebx
    L_00408d0d:
        mov dword ptr fs:[0],ecx
    L_00408d14:
        add esp,10h
    L_00408d17:
        ret
    }
}
