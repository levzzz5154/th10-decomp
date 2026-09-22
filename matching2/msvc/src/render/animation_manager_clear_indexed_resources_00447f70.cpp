// BLOCKED (D3506): closest_byte_count=0/87; first_diff=0x00447F70;
// residual_class=private EDI manager/ESI index inputs, two virtual-release
// calls, and the free callee whose native register schedule depends on real
// animation-manager callers.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee topology, and a readable opaque-layout candidate (103-byte
// standalone extent; rejected before byte comparison); schema-2/native-LTCG
// registration cannot proceed while the exclusive region remains kind asm.
// next_lever=native-LTCG schema-2 cluster over callers 0x0040B7B0 and
// 0x00448450 with this body and the virtual/free callees, then measure the
// complete 87-byte contribution before changing ownership.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00447F70..0x00447FC6: ?AnimationManager_ClearIndexedResources@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearIndexedResources_00447f70() {
    __asm {
    L_00447f70:
        mov eax,dword ptr [edi+esi*4+3AD4E0h]
    L_00447f77:
        push ebx
    L_00447f78:
        xor ebx,ebx
    L_00447f7a:
        cmp eax,ebx
    L_00447f7c:
        je short L_00447f8b
    L_00447f7e:
        mov ecx,dword ptr [eax]
    L_00447f80:
        push eax
    L_00447f81:
        call dword ptr [ecx+8]
    L_00447f84:
        mov dword ptr [edi+esi*4+3AD4E0h],ebx
    L_00447f8b:
        mov eax,dword ptr [edi+esi*4+3AD560h]
    L_00447f92:
        cmp eax,ebx
    L_00447f94:
        je short L_00447fa3
    L_00447f96:
        mov edx,dword ptr [eax]
    L_00447f98:
        push eax
    L_00447f99:
        call dword ptr [edx+8]
    L_00447f9c:
        mov dword ptr [edi+esi*4+3AD560h],ebx
    L_00447fa3:
        mov eax,dword ptr [edi+esi*4+3AD5E0h]
    L_00447faa:
        cmp eax,ebx
    L_00447fac:
        je short L_00447fbe
    L_00447fae:
        push eax
    L_00447faf:
        call asm_free_00452422
    L_00447fb4:
        add esp,4
    L_00447fb7:
        mov dword ptr [edi+esi*4+3AD5E0h],ebx
    L_00447fbe:
        mov dword ptr [edi+esi*4+3AD5E0h],ebx
    L_00447fc5:
        pop ebx
    L_00447fc6:
        ret
    }
}
