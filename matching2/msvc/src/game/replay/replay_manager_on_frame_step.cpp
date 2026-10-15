#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A3E0: the replay manager's frame-step task, registered by 0x00428F60.
// BLOCKED (near miss): frame-step callback stored twice by 0x00428F60; this in
// ECX.  Returns 6 when the game UI (0x00477810) exists without flag 4 in +0x58,
// state (+0x10) == 1, bit 0x100 of 0x00474E30 is set and frame (+0x1C8) % 4 != 0,
// else 1.  Best source (plain /O2 and native LTCG agree):
//   if (ui) { if (ui->flags & 4) return 1;
//             if (state == 1 && (flags & 0x100) && frame % 4) return 6;
//             return 1; }
//   return 1;
// Every instruction matches; only the four failure branches target the final
// ret (+0x43) instead of the ret after `mov eax,6` (+0x3D).  Variants using a
// result variable move that ret right but hoist `mov eax,1` above the null
// check (UI pointer in EDX).  About 20 shapes were tried.

// BLOCKED (H2901): retail is exact only with the existing private-ABI overlay.
// Ghidra confirms a 68-byte span at 0x0042A3E0 with no function boundary, two
// data reads (0x00477810 and 0x00474E30), and incoming xrefs from 0x004291B5
// and 0x004293F1 in FUN_00428F60.  The readable __fastcall candidate was
// semantically faithful but emitted 65 bytes, first differing at 0x0042A3E7
// because MSVC moved the result initialization before the scene test; a
// branch-structured candidate emitted 64 bytes (first differing at the same
// control-flow shape), and a goto/private-label candidate emitted 80 bytes due
// to an ECX save.  variants_tested=early-return __fastcall (65/68),
// consolidated result __fastcall (65/68), branch-structured result (64/68),
// goto-shaped private-ABI result (80/68). next_lever=retain a real LTCG caller
// cluster that supplies ECX as this and preserves the retail dual-return layout;
// no readable exact candidate was found under the standalone MSVC 13.10 ABI.
// closest_byte_count=65/68 among readable candidates; first_diff=0x0042A3E7;
// residual_class=private-ABI dual-return control flow.
// 0x0042A3E0..0x0042A423: FUN_0042a3e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl ReplayManager_OnFrameStep() {
    __asm {
    L_0042a3e0:
        mov eax,dword ptr [data_00477810]
    L_0042a3e5:
        test eax,eax
    L_0042a3e7:
        je short L_0042a41e
    L_0042a3e9:
        test byte ptr [eax+58h],4
    L_0042a3ed:
        mov eax,1
    L_0042a3f2:
        jne short L_0042a41d
    L_0042a3f4:
        cmp dword ptr [ecx+10h],eax
    L_0042a3f7:
        jne short L_0042a41d
    L_0042a3f9:
        mov edx,dword ptr [data_00474e30]
    L_0042a3ff:
        test dh,al
    L_0042a401:
        je short L_0042a41d
    L_0042a403:
        mov ecx,dword ptr [ecx+1C8h]
    L_0042a409:
        and ecx,80000003h
    L_0042a40f:
        jns short L_0042a416
    L_0042a411:
        dec ecx
    L_0042a412:
        or ecx,0FFFFFFFCh
    L_0042a415:
        inc ecx
    L_0042a416:
        je short L_0042a41d
    L_0042a418:
        mov eax,6
    L_0042a41d:
        ret
    L_0042a41e:
        mov eax,1
    L_0042a423:
        ret
    }
}
