// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00427d50.cpp"

#pragma code_seg(".text$03context")
int __stdcall PairDifferenceContext(
    Pair_00427d50* outputs,
    Pair_00427d50** lefts,
    Pair_00427d50** rights,
    int count) {
    while (count--) {
        *outputs = **lefts - **rights;
        ++outputs;
        ++lefts;
        ++rights;
    }
    return 0;
}
#pragma code_seg()
