#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462E7E..0x00462EF0: ___FrameUnwindToState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameUnwindToState_00462e7e() {
    __asm {
    L_00462e7e:
        push 10h
    L_00462e80:
        push 46CAA8h
    L_00462e85:
        call asm_SEH_prolog_00454bbc
    L_00462e8a:
        mov ebx,dword ptr [ebp+8]
    L_00462e8d:
        mov esi,dword ptr [ebx+8]
    L_00462e90:
        mov dword ptr [ebp-1Ch],esi
    L_00462e93:
        call asm_getptd_00456357
    L_00462e98:
        add eax,84h
    L_00462e9d:
        inc dword ptr [eax]
    L_00462e9f:
        and dword ptr [ebp-4],0
    L_00462ea3:
        mov edi,dword ptr [ebp+10h]
    L_00462ea6:
        cmp esi,dword ptr [ebp+14h]
    L_00462ea9:
        TH10_REL8(0x74, 0x00462ea9, VA_asm_target_00462f0f)
    L_00462eab:
        cmp esi,0FFFFFFFFh
    L_00462eae:
        jle short L_00462eb5
    L_00462eb0:
        cmp esi,dword ptr [edi+4]
    L_00462eb3:
        jl short L_00462eba
    L_00462eb5:
        call asm_inconsistency_004556e0
    L_00462eba:
        mov eax,esi
    L_00462ebc:
        shl eax,3
    L_00462ebf:
        mov ecx,dword ptr [edi+8]
    L_00462ec2:
        add ecx,eax
    L_00462ec4:
        mov esi,dword ptr [ecx]
    L_00462ec6:
        mov dword ptr [ebp-20h],esi
    L_00462ec9:
        mov dword ptr [ebp-4],1
    L_00462ed0:
        cmp dword ptr [ecx+4],0
    L_00462ed4:
        je short L_00462eeb
    L_00462ed6:
        mov dword ptr [ebx+8],esi
    L_00462ed9:
        push 103h
    L_00462ede:
        push ebx
    L_00462edf:
        mov ecx,dword ptr [edi+8]
    L_00462ee2:
        push dword ptr [ecx+eax+4]
    L_00462ee6:
        call asm_CallSettingFrame_12_00463a10
    L_00462eeb:
        and dword ptr [ebp-4],0
    L_00462eef:
        TH10_REL8(0xeb, 0x00462eef, VA_asm_FrameUnwindToState_part_00462f0a)
    }
}

// 0x00462F0A..0x00462F2A: ___FrameUnwindToState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameUnwindToState_part_00462f0a() {
    __asm {
    L_00462f0a:
        mov dword ptr [ebp-1Ch],esi
    L_00462f0d:
        TH10_REL8(0xeb, 0x00462f0d, VA_asm_target_00462ea6)
    L_00462f0f:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00462f13:
        call asm_FUN_00462f31_00462f31
    L_00462f18:
        cmp esi,dword ptr [ebp+14h]
    L_00462f1b:
        je short L_00462f22
    L_00462f1d:
        call asm_inconsistency_004556e0
    L_00462f22:
        mov dword ptr [ebx+8],esi
    L_00462f25:
        call asm_SEH_epilog_00454bf7
    L_00462f2a:
        ret
    }
}
