// BLOCKED (D3804): closest_byte_count=1/136; first_diff=0x00414830;
// residual_class=compiler-generated SEH registration/unregistration and
// private constructor/destructor ABIs across the 0x9ED0-byte ItemManager
// layout. variants_tested=live Ghidra decompile for 0x00414830 and caller
// 0x00417870 (including 0x00413810, 0x00413980, 0x004145F0), plus an MSVC
// 13.10 standalone readable factory candidate (67-byte extent, 1/136
// comparable bytes); the exact assembly baseline was restored. next_lever=
// schema2 native-LTCG cluster rooted at real caller 0x00417870, with this
// factory, ItemManager constructor/initializer/destructor, operator_new/free,
// and production manager layout/EH bindings co-compiled.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x00414830..0x004148B7: ItemManager_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ItemManager_CreateRetail_00414830() {
    __asm {
    L_00414830:
        push 0FFFFFFFFh
    L_00414832:
        push 46584Bh
    L_00414837:
        mov eax,dword ptr fs:[0]
    L_0041483d:
        push eax
    L_0041483e:
        mov dword ptr fs:[0],esp
    L_00414845:
        push ecx
    L_00414846:
        push ebx
    L_00414847:
        push 9ED0h
    L_0041484c:
        call asm_operator_new_00452493
    L_00414851:
        add esp,4
    L_00414854:
        mov dword ptr [esp+4],eax
    L_00414858:
        test eax,eax
    L_0041485a:
        mov dword ptr [esp+10h],0
    L_00414862:
        je short L_0041486e
    L_00414864:
        push eax
    L_00414865:
        call asm_FUN_00413810_00413810
    L_0041486a:
        mov ebx,eax
    L_0041486c:
        jmp short L_00414870
    L_0041486e:
        xor ebx,ebx
    L_00414870:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00414878:
        call asm_ItemFrontRuntime_InitializeRetail_00413980
    L_0041487d:
        test eax,eax
    L_0041487f:
        je short L_004148a6
    L_00414881:
        test ebx,ebx
    L_00414883:
        je short L_00414894
    L_00414885:
        push ebx
    L_00414886:
        call asm_FUN_004145f0_004145f0
    L_0041488b:
        push ebx
    L_0041488c:
        call asm_free_004524a1
    L_00414891:
        add esp,4
    L_00414894:
        xor eax,eax
    L_00414896:
        pop ebx
    L_00414897:
        mov ecx,dword ptr [esp+4]
    L_0041489b:
        mov dword ptr fs:[0],ecx
    L_004148a2:
        add esp,10h
    L_004148a5:
        ret
    L_004148a6:
        mov ecx,dword ptr [esp+8]
    L_004148aa:
        mov eax,ebx
    L_004148ac:
        pop ebx
    L_004148ad:
        mov dword ptr fs:[0],ecx
    L_004148b4:
        add esp,10h
    L_004148b7:
        ret
    }
}
