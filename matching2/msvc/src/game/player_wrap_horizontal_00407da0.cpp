#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.

// 0x00407DA0..0x00407E33: Player_WrapHorizontal
// Naked body preserves the retail register/stack ABI.
// BLOCKED: closest_byte_count=148/148; first_diff=none (retail assembly baseline);
// residual_class=EBX receiver with EAX return and private x87/control-flow
// register state across Entity_PointWithinBoundsInclusive and FrameTimer calls;
// variants_tested=Ghidra pseudocode plus caller register inspection; no
// source-only candidate accepted; next_lever=co-compile the real bullet-runtime
// caller and callee chain in schema-2 native LTCG.
extern "C" __declspec(naked) void __cdecl asm_Player_WrapHorizontal_00407da0() {
    __asm {
    L_00407da0:
        mov edx,dword ptr [ebx+39Ch]
    L_00407da6:
        mov eax,dword ptr [edx+30h]
    L_00407da9:
        push eax
    L_00407daa:
        mov eax,dword ptr [edx+34h]
    L_00407dad:
        lea ecx,[ebx+3B4h]
    L_00407db3:
        push eax
    L_00407db4:
        call asm_Entity_PointWithinBoundsInclusive_004061d0
    L_00407db9:
        test eax,eax
    L_00407dbb:
        je short L_00407e33
    L_00407dbd:
        fld dword ptr [ecx]
    L_00407dbf:
        push esi
    L_00407dc0:
        fcomp dword ptr [data_00470b40]
    L_00407dc6:
        push edi
    L_00407dc7:
        fnstsw ax
    L_00407dc9:
        test ah,5
    L_00407dcc:
        jp short L_00407ddb
    L_00407dce:
        fld dword ptr [edx+34h]
    L_00407dd1:
        fadd dword ptr [ecx]
    L_00407dd3:
        fadd dword ptr [data_00470b54]
    L_00407dd9:
        jmp short L_00407df5
    L_00407ddb:
        fld dword ptr [ecx]
    L_00407ddd:
        fcomp dword ptr [data_00470b3c]
    L_00407de3:
        fnstsw ax
    L_00407de5:
        test ah,41h
    L_00407de8:
        jne short L_00407e1d
    L_00407dea:
        fld dword ptr [edx+34h]
    L_00407ded:
        fadd dword ptr [data_00470b54]
    L_00407df3:
        fsubr dword ptr [ecx]
    L_00407df5:
        lea esi,[ebx+74Ch]
    L_00407dfb:
        fstp dword ptr [ecx]
    L_00407dfd:
        push 0BF800000h
    L_00407e02:
        call asm_FrameTimer_Advance_0044bf40
    L_00407e07:
        mov edi,dword ptr [ebx+458h]
    L_00407e0d:
        test edi,edi
    L_00407e0f:
        jl short L_00407e1d
    L_00407e11:
        mov ecx,492590h
    L_00407e16:
        push 0
    L_00407e18:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407e1d:
        mov eax,dword ptr [ebx+750h]
    L_00407e23:
        test eax,eax
    L_00407e25:
        pop edi
    L_00407e26:
        pop esi
    L_00407e27:
        jg short L_00407e33
    L_00407e29:
        xor dword ptr [ebx+43Ch],100000h
    L_00407e33:
        ret
    }
}
