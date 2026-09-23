#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3706): closest_byte_count=9/172; first_diff=0x00407E40
// residual_class=private EBX receiver with EDX live from the bounds helper,
// x87 comparison/order, and caller-selected FrameTimer/animation ABIs.
// variants_tested=live Ghidra decompile plus typed Player/Entity readable
// member candidate under MSVC 13.10; candidate was 189 bytes and restored.
// next_lever=schema-2 native-LTCG cluster over the real player update caller,
// bounds helper, FrameTimer, and animation queue.

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.

// 0x00407E40..0x00407EEB: Player_WrapVertical
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_WrapVertical_00407e40() {
    __asm {
    L_00407e40:
        mov edx,dword ptr [ebx+39Ch]
    L_00407e46:
        mov eax,dword ptr [edx+30h]
    L_00407e49:
        mov ecx,dword ptr [edx+34h]
    L_00407e4c:
        push eax
    L_00407e4d:
        push ecx
    L_00407e4e:
        lea ecx,[ebx+3B4h]
    L_00407e54:
        call asm_Entity_PointWithinBoundsInclusive_004061d0
    L_00407e59:
        test eax,eax
    L_00407e5b:
        je asm_target_00407eeb
    L_00407e61:
        fld dword ptr [ebx+3B8h]
    L_00407e67:
        push esi
    L_00407e68:
        fcomp qword ptr [data_00470b70]
    L_00407e6e:
        push edi
    L_00407e6f:
        fnstsw ax
    L_00407e71:
        test ah,5
    L_00407e74:
        jp short L_00407e87
    L_00407e76:
        fld dword ptr [edx+30h]
    L_00407e79:
        fadd dword ptr [ebx+3B8h]
    L_00407e7f:
        fadd dword ptr [data_00470b38]
    L_00407e85:
        jmp short L_00407ea9
    L_00407e87:
        fld dword ptr [ebx+3B8h]
    L_00407e8d:
        fcomp dword ptr [data_00470b38]
    L_00407e93:
        fnstsw ax
    L_00407e95:
        test ah,41h
    L_00407e98:
        jne short L_00407ed5
    L_00407e9a:
        fld dword ptr [edx+30h]
    L_00407e9d:
        fadd dword ptr [data_00470b38]
    L_00407ea3:
        fsubr dword ptr [ebx+3B8h]
    L_00407ea9:
        lea esi,[ebx+780h]
    L_00407eaf:
        fstp dword ptr [ebx+3B8h]
    L_00407eb5:
        push 0BF800000h
    L_00407eba:
        call asm_FrameTimer_Advance_0044bf40
    L_00407ebf:
        mov edi,dword ptr [ebx+458h]
    L_00407ec5:
        test edi,edi
    L_00407ec7:
        jl short L_00407ed5
    L_00407ec9:
        mov ecx,492590h
    L_00407ece:
        push 0
    L_00407ed0:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407ed5:
        mov eax,dword ptr [ebx+784h]
    L_00407edb:
        test eax,eax
    L_00407edd:
        pop edi
    L_00407ede:
        pop esi
    L_00407edf:
        jg short L_00407eeb
    L_00407ee1:
        xor dword ptr [ebx+43Ch],200000h
    L_00407eeb:
        ret
    }
}
