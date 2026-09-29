// Complete candidate: reference/semantic_candidates/sound_stream_recreate.cpp.
// See recovery_notes/sound_stream_initialization_and_creation.md for current
// ownership, callback, notification and differential evidence. Native matching
// remains pending; the following byte probe is historical.
// BLOCKED (D3404): closest_byte_count=0/338; first_diff=0x0044CF20;
// residual_class=private ESI receiver, COM-style virtual slot ABI, object
// layout at +0x4/+0x10/+0x58, and cleanup/error-path register scheduling.
// variants_tested=live Ghidra decompilation and caller 0x0043DDF0, typed
// virtual-dispatch/raw-layout MSVC 13.10 candidate (299/338 extent).
// next_lever=schema2 native-LTCG over caller 0x0043DDF0, this body, the
// factory/resource virtual slots, and verified interface layouts; preserve ESI
// and all HRESULT cleanup paths.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044CF20..0x0044D071: FUN_0044cf20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044cf20_0044cf20() {
    __asm {
    L_0044cf20:
        push ecx
    L_0044cf21:
        mov eax,dword ptr [esi+10h]
    L_0044cf24:
        push ebx
    L_0044cf25:
        push ebp
    L_0044cf26:
        xor ebx,ebx
    L_0044cf28:
        push edi
    L_0044cf29:
        xor edi,edi
    L_0044cf2b:
        cmp eax,ebx
    L_0044cf2d:
        mov dword ptr [esi+30h],ebx
    L_0044cf30:
        jbe short L_0044cf55
    L_0044cf32:
        mov eax,dword ptr [esi+4]
    L_0044cf35:
        mov ecx,dword ptr [eax+edi*4]
    L_0044cf38:
        cmp ecx,ebx
    L_0044cf3a:
        lea eax,[eax+edi*4]
    L_0044cf3d:
        je short L_0044cf4d
    L_0044cf3f:
        mov eax,ecx
    L_0044cf41:
        mov ecx,dword ptr [eax]
    L_0044cf43:
        push eax
    L_0044cf44:
        call dword ptr [ecx+8]
    L_0044cf47:
        mov edx,dword ptr [esi+4]
    L_0044cf4a:
        mov dword ptr [edx+edi*4],ebx
    L_0044cf4d:
        mov eax,dword ptr [esi+10h]
    L_0044cf50:
        inc edi
    L_0044cf51:
        cmp edi,eax
    L_0044cf53:
        jb short L_0044cf32
    L_0044cf55:
        mov eax,dword ptr [esi+4]
    L_0044cf58:
        cmp eax,ebx
    L_0044cf5a:
        je short L_0044cf68
    L_0044cf5c:
        push eax
    L_0044cf5d:
        call asm_free_004524a1
    L_0044cf62:
        add esp,4
    L_0044cf65:
        mov dword ptr [esi+4],ebx
    L_0044cf68:
        mov eax,dword ptr [esi+10h]
    L_0044cf6b:
        shl eax,2
    L_0044cf6e:
        push eax
    L_0044cf6f:
        mov dword ptr [esp+10h],ebx
    L_0044cf73:
        call asm_operator_new_00452493
    L_0044cf78:
        mov dword ptr [esi+4],eax
    L_0044cf7b:
        mov eax,dword ptr [esi+10h]
    L_0044cf7e:
        add esp,4
    L_0044cf81:
        cmp eax,ebx
    L_0044cf83:
        jbe asm_target_0044d03c
    L_0044cf89:
        lea ebp,[esi+34h]
    L_0044cf8c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0044cf90:
        mov ecx,dword ptr [esi+58h]
    L_0044cf93:
        mov eax,dword ptr [ecx]
    L_0044cf95:
        mov ecx,dword ptr [esi+4]
    L_0044cf98:
        mov edx,dword ptr [eax]
    L_0044cf9a:
        push 0
    L_0044cf9c:
        lea edi,[ebx*4]
    L_0044cfa3:
        add ecx,edi
    L_0044cfa5:
        push ecx
    L_0044cfa6:
        push ebp
    L_0044cfa7:
        push eax
    L_0044cfa8:
        call dword ptr [edx+0Ch]
    L_0044cfab:
        test eax,eax
    L_0044cfad:
        jl asm_target_0044d068
    L_0044cfb3:
        mov edx,dword ptr [esi+4]
    L_0044cfb6:
        mov edi,dword ptr [edi+edx]
    L_0044cfb9:
        mov eax,dword ptr [edi]
    L_0044cfbb:
        lea ecx,[esp+0Ch]
    L_0044cfbf:
        push ecx
    L_0044cfc0:
        push 46743Ch
    L_0044cfc5:
        push edi
    L_0044cfc6:
        call dword ptr [eax]
    L_0044cfc8:
        test eax,eax
    L_0044cfca:
        jl asm_target_0044d068
    L_0044cfd0:
        push 80h
    L_0044cfd5:
        call asm_operator_new_00452493
    L_0044cfda:
        mov edi,eax
    L_0044cfdc:
        add esp,4
    L_0044cfdf:
        test edi,edi
    L_0044cfe1:
        je short L_0044d043
    L_0044cfe3:
        xor eax,eax
    L_0044cfe5:
        mov edx,dword ptr [esi+6Ch]
    L_0044cfe8:
        lea ecx,[eax+1]
    L_0044cfeb:
        imul edx,ecx
    L_0044cfee:
        dec edx
    L_0044cfef:
        mov dword ptr [edi+eax*8],edx
    L_0044cff2:
        mov edx,dword ptr [esi+70h]
    L_0044cff5:
        mov dword ptr [edi+eax*8+4],edx
    L_0044cff9:
        mov eax,ecx
    L_0044cffb:
        cmp eax,10h
    L_0044cffe:
        jb short L_0044cfe5
    L_0044d000:
        mov eax,dword ptr [esp+0Ch]
    L_0044d004:
        mov ecx,dword ptr [eax]
    L_0044d006:
        push edi
    L_0044d007:
        push 10h
    L_0044d009:
        push eax
    L_0044d00a:
        call dword ptr [ecx+0Ch]
    L_0044d00d:
        test eax,eax
    L_0044d00f:
        mov eax,dword ptr [esp+0Ch]
    L_0044d013:
        jl short L_0044d04d
    L_0044d015:
        test eax,eax
    L_0044d017:
        je short L_0044d027
    L_0044d019:
        mov edx,dword ptr [eax]
    L_0044d01b:
        push eax
    L_0044d01c:
        call dword ptr [edx+8]
    L_0044d01f:
        mov dword ptr [esp+0Ch],0
    L_0044d027:
        push edi
    L_0044d028:
        call asm_free_004524a1
    L_0044d02d:
        mov eax,dword ptr [esi+10h]
    L_0044d030:
        add esp,4
    L_0044d033:
        inc ebx
    L_0044d034:
        cmp ebx,eax
    L_0044d036:
        jb asm_target_0044cf90
    L_0044d03c:
        pop edi
    L_0044d03d:
        pop ebp
    L_0044d03e:
        xor eax,eax
    L_0044d040:
        pop ebx
    L_0044d041:
        pop ecx
    L_0044d042:
        ret
    L_0044d043:
        pop edi
    L_0044d044:
        pop ebp
    L_0044d045:
        mov eax,8007000Eh
    L_0044d04a:
        pop ebx
    L_0044d04b:
        pop ecx
    L_0044d04c:
        ret
    L_0044d04d:
        test eax,eax
    L_0044d04f:
        je short L_0044d05f
    L_0044d051:
        mov ecx,dword ptr [eax]
    L_0044d053:
        push eax
    L_0044d054:
        call dword ptr [ecx+8]
    L_0044d057:
        mov dword ptr [esp+0Ch],0
    L_0044d05f:
        push edi
    L_0044d060:
        call asm_free_004524a1
    L_0044d065:
        add esp,4
    L_0044d068:
        pop edi
    L_0044d069:
        pop ebp
    L_0044d06a:
        mov eax,80004005h
    L_0044d06f:
        pop ebx
    L_0044d070:
        pop ecx
    L_0044d071:
        ret
    }
}
