#pragma once

#include <cstdint>

typedef std::uint8_t ParticleSeedByte;
typedef std::uint32_t ParticleSeedWord;

struct ParticleSeed {
    float values[6];       // +0x00..+0x17
    ParticleSeedByte random[4]; // +0x18..+0x1B
};

typedef ParticleSeedWord (*ParticleRandomHook)();

// Add the six floating-point channels and refresh the four random bytes.
void ParticleSeed_Combine(ParticleSeed* destination,
                          const ParticleSeed* left,
                          const ParticleSeed* right,
                          ParticleRandomHook next_random);
