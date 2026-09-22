#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// BLOCKED (D3102): closest_byte_count=0/84; first_diff=unmeasured;
// residual_class=abi/x87+cluster: the stdcall caller supplies one stack float,
// but the body intentionally carries it in x87 through FUCOMPP/FCOMP/FDIV,
// calls the zero-argument 0x00463B2C helper with ST(0), then passes its EAX
// result plus EAX=0x00492590 and EDX=0x0046D275 to the private
// AnimationManager_RegisterResource call.  A normal float expression changes
// both the x87 compare schedule and the helper's register/stack contract.
// variants_tested=retail naked baseline, Ghidra's five-caller topology,
// typed float/global pseudocode, and the 0x00463B2C/0x0043E460 helper
// signatures; no compiler-readable candidate was byte-measured.
// next_lever=co-compile this worker with 0x00463B2C and
// AnimationManager_RegisterResource_0043E460 in a native-LTCG sound cluster
// that preserves ST(0), EAX, and EDX across the private calls.

// 0x00420C30..0x00420C83: Sound_PlayRandomVoiceRetail
// Naked body preserves the retail register/stack ABI.

// 0x00420C30..0x00420C83: Sound_PlayRandomVoiceRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Sound_PlayRandomVoiceRetail_00420c30() {
    __asm {
    L_00420c30:
        fld dword ptr [data_00470b04]
    L_00420c36:
        fld dword ptr [data_00476f78]
    L_00420c3c:
        fucompp
    L_00420c3e:
        fnstsw ax
    L_00420c40:
        test ah,44h
    L_00420c43:
        jp short L_00420c4b
    L_00420c45:
        fld dword ptr [esp+4]
    L_00420c49:
        jmp short L_00420c68
    L_00420c4b:
        fld dword ptr [data_00476f78]
    L_00420c51:
        fcomp dword ptr [data_00470afc]
    L_00420c57:
        fld dword ptr [esp+4]
    L_00420c5b:
        fnstsw ax
    L_00420c5d:
        test ah,41h
    L_00420c60:
        je short L_00420c68
    L_00420c62:
        fdiv dword ptr [data_00476f78]
    L_00420c68:
        call asm_FUN_00463b2c_00463b2c
    L_00420c6d:
        push eax
    L_00420c6e:
        push 5
    L_00420c70:
        mov edx,46D275h
    L_00420c75:
        mov eax,492590h
    L_00420c7a:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c7f:
        xor eax,eax
    L_00420c81:
        ret 4
    }
}
