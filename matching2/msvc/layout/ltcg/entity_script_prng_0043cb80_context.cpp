// Compiler context only; never selected as recovered game code.
#include "../../src/script/prng.cpp"

#pragma code_seg(".text$03context")
unsigned int __stdcall EntityScriptPrngCompilerContext(
        EntityScriptRng_0043cb80** states, const unsigned int* moduli, int count) {
    unsigned int total = 0;
    while (count--)
        total += (*states++)->NextRandomModulo(*moduli++);
    return total;
}
#pragma code_seg()
