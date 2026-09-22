// BLOCKED (D2702): closest_byte_count=120; first_diff=0x00420AAE;
// residual_class=EAX-carrying private RegisterResource call plus register
// pressure: a readable 120-byte candidate matched the stack-cookie/copy and
// string rewrite extent but differed in 60 bytes from the retail body.
// variants_tested=exact retail wrapper, the legacy recovery semantic model,
// a stack-copy candidate, and a __stdcall candidate with typed strrchr and
// RegisterResource declarations; the measured candidate's first mismatch was
// the compiler's ESI preservation where retail reloads the stack argument.
// next_lever=native-LTCG schema-2 visibility for RegisterResource's EAX/EDX
// convention (or a fixed-address semantic registration that permits that
// private call), then remeasure the 120-byte contribution.
#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00420A90..0x00420B07: Recovery_ReplaceExtensionWav
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReplaceExtensionWav_00420a90() {
    __asm {
    L_00420a90:
        sub esp,104h
    L_00420a96:
        mov eax,dword ptr [data_00473660]
    L_00420a9b:
        xor eax,esp
    L_00420a9d:
        mov dword ptr [esp+100h],eax
    L_00420aa4:
        mov eax,dword ptr [esp+10Ch]
    L_00420aab:
        lea edx,[esp]
    L_00420aae:
        sub edx,eax
    L_00420ab0:
        mov cl,byte ptr [eax]
    L_00420ab2:
        mov byte ptr [edx+eax],cl
    L_00420ab5:
        inc eax
    L_00420ab6:
        test cl,cl
    L_00420ab8:
        jne short L_00420ab0
    L_00420aba:
        lea eax,[esp]
    L_00420abd:
        push 2Eh
    L_00420abf:
        push eax
    L_00420ac0:
        call asm_strrchr_00452930
    L_00420ac5:
        mov ecx,dword ptr [esp+110h]
    L_00420acc:
        add esp,8
    L_00420acf:
        push ecx
    L_00420ad0:
        mov byte ptr [eax+1],77h
    L_00420ad4:
        mov byte ptr [eax+2],61h
    L_00420ad8:
        mov byte ptr [eax+3],76h
    L_00420adc:
        push 1
    L_00420ade:
        lea edx,[esp+8]
    L_00420ae2:
        mov eax,492590h
    L_00420ae7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420aec:
        mov ecx,dword ptr [esp+100h]
    L_00420af3:
        xor ecx,esp
    L_00420af5:
        mov eax,1
    L_00420afa:
        call asm_security_check_cookie_00458ea5
    L_00420aff:
        add esp,104h
    L_00420b05:
        ret 8
    }
}
