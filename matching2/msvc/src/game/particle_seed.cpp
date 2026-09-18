// 0x00404E10: the component-wise sum of two six-float particle-seed records,
// with the destination's four random bytes refreshed from its last four
// components.
//
// Retail: D9 40 14 / D8 41 14   fld [eax+0x14]; fadd [ecx+0x14]
//         ... six sums, pushed back to front
//         D9 1E / D9 5E 04      fstp [esi]; fstp [esi+4]
//         D9 56 08              fst  [esi+8]
//         D9 C1 / D9 5E 0C      fld st(1); fstp [esi+0xC]
//         D9 C2 / D9 5E 10      fld st(2); fstp [esi+0x10]
//         D9 C3 / D9 5E 14      fld st(3); fstp [esi+0x14]
//         E8 .. / 88 46 18      call __ftol2; mov [esi+0x18],al   (x4, random)
//         8B C6                 mov eax,esi
//         C3                    ret
// The other operand arrives in EAX, the receiver in ECX and the destination in
// ESI, so the sum is compiled as a native-LTCG cluster.
// Carved out of this file (asm_ParticleSeed_Combine_00404e10).

struct ParticleSeed {
    float values[6];
    unsigned char random[4];

    __declspec(noinline) ParticleSeed* Combine(const ParticleSeed* other,
                                               ParticleSeed* destination) const;
};

#pragma code_seg(".text$01seedcombine")
ParticleSeed* ParticleSeed::Combine(const ParticleSeed* other,
                                    ParticleSeed* destination) const {
    // The six sums are computed last-to-first: retail's x87 pushes run back to
    // front, and only that order keeps all six in registers.
    float value5 = values[5] + other->values[5];
    float value4 = values[4] + other->values[4];
    float value3 = values[3] + other->values[3];
    float value2 = values[2] + other->values[2];
    float value1 = values[1] + other->values[1];
    float value0 = values[0] + other->values[0];
    destination->values[0] = value0;
    destination->values[1] = value1;
    destination->values[2] = value2;
    destination->values[3] = value3;
    destination->values[4] = value4;
    destination->values[5] = value5;
    // The random bytes are the truncated sums of the last four components;
    // retail reaches them through __ftol2, of whose result only AL is kept.
    destination->random[0] = (unsigned char)value2;
    destination->random[1] = (unsigned char)value3;
    destination->random[2] = (unsigned char)value4;
    destination->random[3] = (unsigned char)value5;
    return destination;
}
#pragma code_seg()
