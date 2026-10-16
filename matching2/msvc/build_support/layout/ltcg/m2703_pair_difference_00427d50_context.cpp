// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_427d50.cpp"

#pragma code_seg(".text$03context")
int __stdcall PairDifferenceContext(
    Pair6* outputs,
    Pair6** lefts,
    Pair6** rights,
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
