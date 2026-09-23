// BLOCKED (D2702): Ghidra confirms this is __stdcall with two stack arguments
// and RET 8. It copies the source path, rewrites the three bytes after the last
// '.', then calls RegisterResource with its manager in EAX, the local name in
// EDX, and stack arguments 1 and the first wrapper argument. RegisterResource
// itself uses this private EAX/EDX-plus-two-stack-arguments ABI and RET 8; a
// normal MSVC C++ prototype cannot issue that call. The prior semantic
// candidate was 121 bytes and also saved/hoisted the stack argument through
// ESI; its closest match was 120 bytes. Do not promote until the compiler can
// express the callee's private ABI across this call and the other
// RegisterResource callers, then recheck both call-site registers and frame
// layout. See recovery_replace_extension_wav_00420a90.md.
#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00420A90..0x00420B07: Recovery_ReplaceExtensionWav
// Semantics: (registration selector, source path) -> 1. The selector is passed
// to RegisterResource as its second stack argument; it is not an output pointer.
// Naked body preserves the private EAX/EDX RegisterResource call ABI.
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
