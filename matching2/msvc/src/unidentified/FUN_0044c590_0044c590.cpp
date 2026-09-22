#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (H2901): Ghidra confirms an exact 57-byte leaf span at 0x0044C590
// with no function boundary, incoming xrefs, or outgoing xrefs.  The body
// receives its sole Vector3 pointer in ESI, calls 0x00452FF0 twice through
// x87 double arguments, and writes the converted results back to +0/+4.
// Standalone __thiscall/__fastcall declarations cannot receive this receiver
// in ESI, and the x87 call sequence is compiler-sensitive. variants_tested=ABI
// feasibility inspection and x87 call-shape review; no candidate source was
// retained because the receiver register and floating-point stack sequence
// are both unconstrained without a caller cluster. next_lever=retain a real
// caller/native LTCG context that supplies ESI and the exact helper prototype.
// closest_byte_count=57/57 (existing overlay); first_diff=N/A for overlay;
// residual_class=private-ABI ESI receiver plus x87 call shape.
// 0x0044C590..0x0044C5C8: FUN_0044c590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c590_0044c590() {
    __asm {
    L_0044c590:
        fld dword ptr [esi]
    L_0044c592:
        sub esp,8
    L_0044c595:
        fmul dword ptr [data_00470b44]
    L_0044c59b:
        fstp qword ptr [esp]
    L_0044c59e:
        call asm_FUN_00452ff0_00452ff0
    L_0044c5a3:
        fmul dword ptr [data_00470b00]
    L_0044c5a9:
        fstp dword ptr [esi]
    L_0044c5ab:
        fld dword ptr [esi+4]
    L_0044c5ae:
        fmul dword ptr [data_00470b44]
    L_0044c5b4:
        fstp qword ptr [esp]
    L_0044c5b7:
        call asm_FUN_00452ff0_00452ff0
    L_0044c5bc:
        fmul dword ptr [data_00470b00]
    L_0044c5c2:
        add esp,8
    L_0044c5c5:
        fstp dword ptr [esi+4]
    L_0044c5c8:
        ret
    }
}
