#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409220..0x00409229: FUN_00409220
// Live Ghidra confirms this callback adapter receives its object in ECX,
// moves it to EDI, then enters 0x00408D60.  That callee's machine body reads
// the object through EDI (Ghidra's decompiler calls it `unaff_EDI`), so an
// ordinary C++ forwarding call cannot preserve the actual callee contract.
// Keep the small adapter in assembly until 0x00408D60 and its EDI-based state
// accesses are reconstructed in a shared caller context.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409220_00409220() {
    __asm {
    L_00409220:
        push edi
    L_00409221:
        mov edi,ecx
    L_00409223:
        call asm_FUN_00408d60_00408d60
    L_00409228:
        pop edi
    L_00409229:
        ret
    }
}
