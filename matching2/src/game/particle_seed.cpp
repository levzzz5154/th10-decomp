#include "th10/game/particle_seed.hpp"

#ifdef _MSC_VER
extern "C" void sub_463B2C(void);
#endif

// 0x00404E10 - Combine two six-channel particle parameter blocks. Retail's
// fastcall body receives the three pointers through registers, adds every
// float channel, then takes the low byte from four consecutive RNG calls.
#ifdef _MSC_VER
__declspec(naked) void ParticleSeed_Combine(
        ParticleSeed* destination,
        const ParticleSeed* left,
        const ParticleSeed* right,
        ParticleRandomHook next_random) {
    __asm {
        fld dword ptr [eax+14h]
        fadd dword ptr [ecx+14h]
        fld dword ptr [eax+10h]
        fadd dword ptr [ecx+10h]
        fld dword ptr [eax+0Ch]
        fadd dword ptr [ecx+0Ch]
        fld dword ptr [eax+8]
        fadd dword ptr [ecx+8]
        fld dword ptr [eax+4]
        fadd dword ptr [ecx+4]
        fld dword ptr [eax]
        fadd dword ptr [ecx]
        fstp dword ptr [esi]
        fstp dword ptr [esi+4]
        fst dword ptr [esi+8]
        fld st(1)
        fstp dword ptr [esi+0Ch]
        fld st(2)
        fstp dword ptr [esi+10h]
        fld st(3)
        fstp dword ptr [esi+14h]
        call sub_463B2C
        mov byte ptr [esi+18h], al
        call sub_463B2C
        mov byte ptr [esi+19h], al
        call sub_463B2C
        mov byte ptr [esi+1Ah], al
        call sub_463B2C
        mov byte ptr [esi+1Bh], al
        mov eax, esi
        ret
    }
}
#else
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
#endif
