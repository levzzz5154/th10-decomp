// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the other operand in EAX, the receiver in ECX
// and the destination in ESI.
#include "../../src/game/particle_seed.cpp"

#pragma code_seg(".text$03context")
int __stdcall ParticleSeedCombineCompilerContext(ParticleSeed** left, ParticleSeed** right,
                                                 ParticleSeed* destination, int count) {
    while (count--) {
        destination = (*left++)->Combine(*right++, destination);
    }
    return 0;
}
#pragma code_seg()
