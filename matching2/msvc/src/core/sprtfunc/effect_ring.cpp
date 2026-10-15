// 0x004452F0: build the ring of particles for one effect entity.
//
// Any previous state block is released and a fresh 0x4B0-byte block is
// allocated. Record 0 is the centre; records 1..31 are placed on a circle of
// radius 80 +- 8 around the entity, each with a texture coordinate on a half
// unit circle and a radial drift that random-walks inside +-1/15.
#include "th10/math/rng.hpp"

extern "C" RngState g_rng;
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl entry_free_00452422(void* block);

// The loop draws from the shared generator inline: two steps through a 32-bit
// read of the seed, with the final word filling both halves.
__forceinline unsigned int SharedRng_NextU32() {
    unsigned int value = *(unsigned int*)&g_rng.seed;
    value ^= 0x9630;
    value -= 0x6553;
    unsigned int high = ((unsigned short)value) >> 14;
    g_rng.seed = (unsigned short)(high + (value << 2));
    ++g_rng.generation;
    value = *(unsigned int*)&g_rng.seed;
    value ^= 0x9630;
    value -= 0x6553;
    high = ((unsigned short)value) >> 14;
    g_rng.seed = (unsigned short)(high + (value << 2));
    ++g_rng.generation;
    unsigned int word = g_rng.seed;
    return (word << 16) | word;
}
__forceinline float SharedRng_NextFloatSigned() {
    float roll = (float)SharedRng_NextU32();
    return roll * (1.0f / 2147483648.0f) - 1.0f;
}

struct Vector2_004458b0 {
    float x, y;
    Vector2_004458b0* SetPolar(float angle, float radius);
};

struct RingVector3_004452f0 {
    float x, y, z;
    RingVector3_004452f0() {}
    RingVector3_004452f0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    RingVector3_004452f0 operator+(const RingVector3_004452f0& other) const {
        return RingVector3_004452f0(x + other.x, y + other.y, z + other.z);
    }
    RingVector3_004452f0& operator+=(const RingVector3_004452f0& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};

struct RingParticle_004452f0 {
    RingVector3_004452f0 position;  // +0x00
    float scale;                    // +0x0C
    unsigned int color;             // +0x10
    float u;                        // +0x14
    float v;                        // +0x18
};

struct RingState_004452f0 {
    RingParticle_004452f0 particles[33];  // +0x000
    unsigned char unknown_39C[0x3A0 - 0x39C];
    float radii[33];                // +0x3A0
    float drifts[32];               // +0x424
    float scroll_rate;              // +0x4A4
    float spare_rate;               // +0x4A8
    unsigned char unknown_4AC[0x4B0 - 0x4AC];
};

struct RingEntity_004452f0 {
    unsigned char unknown_000[0x334];
    RingVector3_004452f0 base;      // +0x334
    RingVector3_004452f0 position;  // +0x340
    unsigned char unknown_34C[0x358 - 0x34C];
    RingState_004452f0* state;      // +0x358
    unsigned char unknown_35C[0x398 - 0x35C];
    int (RingEntity_004452f0::*on_update)();  // +0x398
    int (RingEntity_004452f0::*on_draw)();    // +0x39C

    int Advance();
    int DrawFan33();
    __declspec(noinline) int BuildRing();
};

#pragma code_seg(".text$02buildring")
int RingEntity_004452f0::BuildRing() {
    if (state) {
        entry_free_00452422(state);
        state = 0;
    }
    RingState_004452f0* ring = (RingState_004452f0*)asm_malloc_00452706(sizeof(RingState_004452f0));
    state = ring;
    on_update = &RingEntity_004452f0::Advance;
    on_draw = &RingEntity_004452f0::DrawFan33;
    ring->scroll_rate = Rng_NextFloatSigned(&g_rng) * (1.0f / 120.0f);
    ring->spare_rate = Rng_NextFloatSigned(&g_rng) * (1.0f / 120.0f);

    float angle = -3.14159265358979323846f;
    RingParticle_004452f0* particle = ring->particles;
    particle->position = base + position;
    particle->scale = 1.0f;
    particle->u = 0.5f;
    particle->v = 0.5f;
    ++particle;
    float drift = Rng_NextFloatSigned(&g_rng) * (1.0f / 15.0f);

    int index = 0;
    do {
        if (angle >= 3.14159265358979323846f) angle -= 6.28318530717958647692f;
        particle->scale = 1.0f;
        Vector2_004458b0 texture;
        texture.SetPolar(angle, 0.5f);
        particle->position.z = 0.0f;
        particle->u = texture.x + 0.5f;
        particle->v = texture.y + 0.5f;
        ring->radii[index] = SharedRng_NextFloatSigned() * 8.0f + 80.0f;
        ring->drifts[index] = drift;
        float step = SharedRng_NextFloatSigned();
        drift += step * (1.0f / 30.0f);
        if (drift < -(1.0f / 15.0f))
            drift = -(1.0f / 15.0f);
        else if (drift > 1.0f / 15.0f)
            drift = 1.0f / 15.0f;
        float radius = ring->radii[index];
        ((Vector2_004458b0*)particle)->SetPolar(angle, radius);
        particle->position += base + position;
        angle += 0.20268340408802032f;
        ++particle;
    } while (++index < 0x1F);
    return 0;
}
#pragma code_seg()
