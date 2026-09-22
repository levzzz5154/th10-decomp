#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// BLOCKED (D3102): closest_byte_count=0/26; first_diff=unmeasured;
// residual_class=abi/cluster+x87: the 13 ECL VM call sites load the VM in EAX,
// push opcode/value pairs, and expect this wrapper to dereference +0x14D8,
// promote +4 into EAX, forward the value through ECX, then return with RET 8.
// That promoted receiver and the resolver's x87 result are not expressible by
// a standalone __stdcall function.
// variants_tested=retail naked baseline, Ghidra ForwardEclFloat pseudocode,
// the 0x0040E82B..0x0040EC7C caller cluster, and the existing
// ECL_ResolveFloatValue declaration; no compiler-readable candidate was
// byte-measured.
// next_lever=co-compile ForwardEclFloat, ECL_ResolveFloatValue, and the
// ECL VM opcode cluster with native-LTCG EAX pinning and x87 return flow.

// 0x00412AA0..0x00412AB9: Ecl_ForwardFloat
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ecl_ForwardFloat_00412aa0() {
    __asm {
    L_00412aa0:
        mov ecx,dword ptr [esp+8]
    L_00412aa4:
        mov eax,dword ptr [eax+14D8h]
    L_00412aaa:
        mov eax,dword ptr [eax+4]
    L_00412aad:
        push ecx
    L_00412aae:
        mov ecx,dword ptr [esp+8]
    L_00412ab2:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_00412ab7:
        ret 8
    }
}
