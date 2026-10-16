// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_427da0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall CellPairDivideCompilerContext_00427da0(CellPairDivide* item, int divisor) {
    CellPairDivide pair = *item / divisor;
    return pair.first + pair.second;
}
#pragma code_seg()
