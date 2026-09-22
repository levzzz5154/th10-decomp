#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449510..0x00449528: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2702): closest_byte_count=0/25; first_diff=0x00449510;
// residual_class=structural/private ABI: this loop tail is entered by the
// jump from 0x004494D0 with EAX as the intrusive-list cursor and EDX as the
// flag mask; a readable __thiscall member instead uses ECX plus [ESP+4].
// variants_tested=readable child-list Mark(mask) method; MSVC 13.10 emitted
// a 43-byte prologue/loop (including an initial null check) rather than the
// 25-byte retail tail, so no byte prefix is reusable.
// next_lever=re-carve the coupled 0x004494D0/0x00449510 region and anchor its
// real caller/callee register state in native LTCG, or migrate the manifest.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449510() {
    __asm {
    L_00449510:
        mov ecx,dword ptr [eax]
    L_00449512:
        and dword ptr [ecx+35Ch],0FFFFFFFDh
    L_00449519:
        mov ecx,dword ptr [eax]
    L_0044951b:
        or dword ptr [ecx+35Ch],edx
    L_00449521:
        mov eax,dword ptr [eax+4]
    L_00449524:
        test eax,eax
    L_00449526:
        jne short L_00449510
    L_00449528:
        ret
    }
}
