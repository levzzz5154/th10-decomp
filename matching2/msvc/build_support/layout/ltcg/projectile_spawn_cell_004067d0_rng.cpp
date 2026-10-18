// Compiler context only; this translation unit is never selected as recovered
// game code. It supplies the random generator 0x0044BB20 the selected body
// calls.
#pragma code_seg(".text$0044bb20_fn")
#include "../../../src/core/zunlib/rng.cpp"
#pragma code_seg()
