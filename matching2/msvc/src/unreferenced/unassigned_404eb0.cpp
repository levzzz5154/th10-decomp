#include <math.h>

// 0x00404EB0..0x00404EB8: MSVC's sinf intrinsic lowers to the retail
// FLD/FSIN/RET 4 sequence.  Ghidra reports this as an unlabelled span rather
// than a function; the stdcall prototype is established by the RET 4 ABI.
extern "C" float __stdcall asm_unassigned_00404eb0(float value) {
    return sinf(value);
}
