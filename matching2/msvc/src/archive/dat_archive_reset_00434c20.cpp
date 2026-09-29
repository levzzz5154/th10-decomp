#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// The repaired Reset/Close candidates pass 256 Reset comparisons and DAT
// lifecycle tests. See reference/recovery_notes/archive_cleanup_00434c20_00434d10.md.
// The production pair retains assembly pending private ABI and MSVC matching.

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.
// BLOCKED (H3401): closest_byte_count=5/10; first_diff=0x00434C20;
// residual_class=private ABI/register allocation: readable Reset-to-Close
// wrappers compile as a 5-byte tail jump or public-ECX call, while retail
// preserves the receiver in ESI across the legacy Close body.
// variants_tested=plain __thiscall Reset calling the external Close symbol;
// native-LTCG Reset plus a local noinline Close anchor at 0x00434D10;
// both retained readable layouts and emitted only a tail jump at Reset.
// next_lever=schema-2 native-LTCG link that includes the real Close body (or
// an authoritative private-ESI declaration) so the caller/callee ABI is visible.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Reset_00434c20() {
    __asm {
    L_00434c20:
        push esi
    L_00434c21:
        mov esi,ecx
    L_00434c23:
        call asm_DatArchive_Close_00434d10
    L_00434c28:
        pop esi
    L_00434c29:
        ret
    }
}
