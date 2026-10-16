// Compiler-only caller context; never selected as recovered game code.
// Deliberately include only the readable 00449A00 member; the paired legacy
// reset wrappers at 00449A50 and 00449A70 are not part of this cluster.
#include "../../../src/unreferenced/unassigned_449a00.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall ResetPredicatesCompilerContext(
        ResetRange* range, unsigned int address) {
    return range->Contains(address);
}
#pragma code_seg()
