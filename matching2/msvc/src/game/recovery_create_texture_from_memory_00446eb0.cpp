// BLOCKED (D3703): closest_byte_count=0/132; first_diff=unmeasured;
// residual_class=private EAX mode input, EDX/ESI argument registers, the
// conditional format-table remap, D3DXCreateTextureFromFileInMemoryEx stack
// order, and the post-create ESI receiver call all require the real caller
// under native-LTCG.
// variants_tested=live Ghidra decompile at 0x00446EB0; caller inspection at
// 0x00447511; direct callee/dependency inspection at 0x004465B0 and
// 0x004521CA; unchanged production manifest confirms the exclusive region is
// kind=asm, so no production-valid schema-2 body can be selected here.
// next_lever=co-compile 0x00447511, this body, 0x004465B0, and the D3DX
// import under schema-2 native-LTCG, then promote the region to semantic
// ownership; do not alter regions.json in this assignment.

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00446EB0..0x00446F33: Recovery_CreateTextureFromMemory
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateTextureFromMemory_00446eb0() {
    __asm {
    L_00446eb0:
        push edi
    L_00446eb1:
        mov edi,eax
    L_00446eb3:
        test byte ptr [data_00491d78],1
    L_00446eba:
        je short L_00446edd
    L_00446ebc:
        mov eax,dword ptr [edi*4+46F288h]
    L_00446ec3:
        cmp eax,15h
    L_00446ec6:
        je short L_00446ed8
    L_00446ec8:
        test eax,eax
    L_00446eca:
        je short L_00446ed8
    L_00446ecc:
        cmp eax,14h
    L_00446ecf:
        jne short L_00446edd
    L_00446ed1:
        mov edi,3
    L_00446ed6:
        jmp short L_00446edd
    L_00446ed8:
        mov edi,5
    L_00446edd:
        mov eax,dword ptr [esp+0Ch]
    L_00446ee1:
        mov ecx,dword ptr [edi*4+46F288h]
    L_00446ee8:
        push esi
    L_00446ee9:
        push 0
    L_00446eeb:
        push 0
    L_00446eed:
        push eax
    L_00446eee:
        mov eax,dword ptr [esp+20h]
    L_00446ef2:
        push 0FFFFFFFFh
    L_00446ef4:
        push 1
    L_00446ef6:
        push 1
    L_00446ef8:
        push ecx
    L_00446ef9:
        mov ecx,dword ptr [esi+8]
    L_00446efc:
        push 0
    L_00446efe:
        push 0
    L_00446f00:
        push edx
    L_00446f01:
        mov edx,dword ptr [esi+4]
    L_00446f04:
        push eax
    L_00446f05:
        mov eax,dword ptr [data_00491c30]
    L_00446f0a:
        push ecx
    L_00446f0b:
        push edx
    L_00446f0c:
        push eax
    L_00446f0d:
        call asm_D3DXCreateTextureFromFileInMemoryEx_004521ca
    L_00446f12:
        test eax,eax
    L_00446f14:
        je short L_00446f1d
    L_00446f16:
        or eax,0FFFFFFFFh
    L_00446f19:
        pop edi
    L_00446f1a:
        ret 0Ch
    L_00446f1d:
        mov eax,esi
    L_00446f1f:
        call asm_FUN_004465b0_004465b0
    L_00446f24:
        mov ecx,dword ptr [edi*4+46F2A0h]
    L_00446f2b:
        mov dword ptr [esi+0Ch],ecx
    L_00446f2e:
        xor eax,eax
    L_00446f30:
        pop edi
    L_00446f31:
        ret 0Ch
    }
}
