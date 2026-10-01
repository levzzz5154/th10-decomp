#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421FA0: maintained in src/game/fun_00421fa0_00421fa0.cpp.

// 0x0042ACB0..0x0042ACE6: ScoreFile_InitializeDefaultsRetail
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3704): closest_byte_count=0/274; first_diff=0x0042ACB0;
// residual_class=retail __stdcall ret-4 ABI plus packed 0x437C-byte score
// layout and table data; variants_tested=["live Ghidra decompile at
// 0x0042ACB0", "live caller 0x0042AE60", "MSVC 13.10 schema-2 baseline
// probe"]; next_lever=typed packed ScoreFile layout in the real
// EffectManager_InitializePoolsRetail 0x0042AE60 native-LTCG caller scope.
extern "C" __declspec(naked) void __cdecl asm_ScoreFile_InitializeDefaultsRetail_0042acb0() {
    __asm {
    L_0042acb0:
        push ebx
    L_0042acb1:
        push ebp
    L_0042acb2:
        mov ebp,dword ptr [esp+0Ch]
    L_0042acb6:
        push esi
    L_0042acb7:
        push edi
    L_0042acb8:
        xor eax,eax
    L_0042acba:
        mov ecx,10DFh
    L_0042acbf:
        mov edi,ebp
    L_0042acc1:
        rep stosd
    L_0042acc3:
        xor edx,edx
    L_0042acc5:
        mov word ptr [ebp],5243h
    L_0042accb:
        mov word ptr [ebp+2],dx
    L_0042accf:
        mov dword ptr [ebp+8],437Ch
    L_0042acd6:
        lea eax,[ebp+14h]
    L_0042acd9:
        mov esi,5
    L_0042acde:
        mov edi,edi
    L_0042ace0:
        mov ecx,0F4240h
    L_0042ace5:
        TH10_REL8(0xeb, 0x0042ace5, VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042acf0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_0042acf0:
        mov dword ptr [eax-4],ecx
    L_0042acf3:
        mov byte ptr [eax],1
    L_0042acf6:
        mov ebx,dword ptr [data_0046e858]
    L_0042acfc:
        lea edi,[eax+2]
    L_0042acff:
        mov dword ptr [edi],ebx
    L_0042ad01:
        mov ebx,dword ptr [data_0046e85c]
    L_0042ad07:
        mov dword ptr [edi+4],ebx
    L_0042ad0a:
        mov bl,byte ptr [data_0046e860]
    L_0042ad10:
        mov dword ptr [eax+0Ch],edx
    L_0042ad13:
        mov byte ptr [eax+1],dl
    L_0042ad16:
        sub ecx,186A0h
    L_0042ad1c:
        add eax,18h
    L_0042ad1f:
        cmp ecx,edx
    L_0042ad21:
        mov byte ptr [edi+8],bl
    L_0042ad24:
        jg short L_0042acf0
    L_0042ad26:
        dec esi
    L_0042ad27:
        TH10_REL8(0x75, 0x0042ad27, VA_asm_target_0042ace0)
    L_0042ad29:
        xor esi,esi
    L_0042ad2b:
        mov edi,4743C0h
    L_0042ad30:
        mov edx,3
    L_0042ad35:
        mov ebx,4743C2h
    L_0042ad3a:
        dec edi
    L_0042ad3b:
        mov ecx,1
    L_0042ad40:
        lea eax,[ebp+628h]
    L_0042ad46:
        sub ebx,edx
    L_0042ad48:
        TH10_REL8(0xeb, 0x0042ad48, VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042ad50)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042ad50:
        mov dword ptr [eax-4],esi
    L_0042ad53:
        movsx ebp,byte ptr [ecx+edi]
    L_0042ad57:
        mov dword ptr [eax],ebp
    L_0042ad59:
        mov dword ptr [eax+8Ch],ecx
    L_0042ad5f:
        movsx ebp,byte ptr [ecx+4743C0h]
    L_0042ad66:
        mov dword ptr [eax+90h],ebp
    L_0042ad6c:
        lea ebp,[edx-1]
    L_0042ad6f:
        mov dword ptr [eax+11Ch],ebp
    L_0042ad75:
        movsx ebp,byte ptr [edx+ebx]
    L_0042ad79:
        mov dword ptr [eax+120h],ebp
    L_0042ad7f:
        mov dword ptr [eax+1ACh],edx
    L_0042ad85:
        movsx ebp,byte ptr [edx+4743C0h]
    L_0042ad8c:
        mov dword ptr [eax+1B0h],ebp
    L_0042ad92:
        lea ebp,[esi+4]
    L_0042ad95:
        mov dword ptr [eax+23Ch],ebp
    L_0042ad9b:
        movsx ebp,byte ptr [esi+4743C4h]
    L_0042ada2:
        mov dword ptr [eax+240h],ebp
    L_0042ada8:
        add ecx,5
    L_0042adab:
        add esi,5
    L_0042adae:
        add edx,5
    L_0042adb1:
        add eax,2D0h
    L_0042adb6:
        cmp ecx,6Fh
    L_0042adb9:
        jl short L_0042ad50
    L_0042adbb:
        pop edi
    L_0042adbc:
        pop esi
    L_0042adbd:
        pop ebp
    L_0042adbe:
        pop ebx
    L_0042adbf:
        ret 4
    }
}

// 0x0042B030: maintained in src/game/fun_0042b030_0042b030.cpp.
