#include "th10/game/particle_seed.hpp"


// 0x00404E10 - Combine two six-channel particle parameter blocks. Retail's
// fastcall body receives the three pointers through registers, adds every
// float channel, then takes the low byte from four consecutive RNG calls.
void ParticleSeed_Combine(ParticleSeed* destination,
                          const ParticleSeed* left,
                          const ParticleSeed* right,
                          ParticleRandomHook next_random) {
    for (int index = 0; index < 6; ++index) {
        destination->values[index] =
            left->values[index] + right->values[index];
    }
    for (int index = 0; index < 4; ++index) {
        destination->random[index] =
            static_cast<std::uint8_t>(next_random());
    }
}
