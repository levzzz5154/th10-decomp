// 0x00445620: advance one effect entity's ring of particles.
//
// The entity owns a state block at +0x358. Its particle array starts at the
// block's first byte and every record is 0x1C bytes: position, angle, colour
// and two countdowns. Record 0 carries the accumulated level; the visible ring
// is records 1..31. While a countdown is negative the eleven triples of the
// array have 1.0f added to that field, then each particle's polar placement is
// rebuilt from the running angle and the summed radius, the entity placement is
// added and the next particle is advanced. The tail wraps record 1 into the
// slot after record 31.
struct Vector2_004458b0 {
    float x, y;
    Vector2_004458b0* SetPolar(float angle, float radius);
};

struct EffectVector3_00445620 {
    float x, y, z;
    EffectVector3_00445620() {}
    EffectVector3_00445620(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    EffectVector3_00445620 operator+(const EffectVector3_00445620& other) const {
        return EffectVector3_00445620(x + other.x, y + other.y, z + other.z);
    }
    EffectVector3_00445620& operator+=(const EffectVector3_00445620& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};

struct EffectParticle_00445620 {
    EffectVector3_00445620 position;  // +0x00, world placement
    float angle;                 // +0x0C
    unsigned int color;          // +0x10
    float countdown_a;           // +0x14
    float countdown_b;           // +0x18
};

struct EffectState_00445620 {
    EffectParticle_00445620 particles[33];      // +0x000
    unsigned char unknown_39C[0x3A0 - 0x39C];
    float radii_a[33];           // +0x3A0
    float radii_b[32];           // +0x424, the last slot is the rate below
    float rate;                  // +0x4A4
    float Rate() const { return rate; }
    float RadiusStep(int index) const { return radii_b[index]; }

    __forceinline void RaiseCountdownA() {
        for (int triple = 0; triple < 11; ++triple)
            for (int slot = 0; slot < 3; ++slot)
                particles[3 * triple + slot].countdown_a += 1.0f;
    }
    __forceinline void RaiseCountdownB() {
        for (int triple = 0; triple < 11; ++triple)
            for (int slot = 0; slot < 3; ++slot)
                particles[3 * triple + slot].countdown_b += 1.0f;
    }
};

struct EffectEntity_00445620 {
    unsigned char unknown_000[0x2FC];
    unsigned int color;          // +0x2FC
    unsigned char unknown_300[0x334 - 0x300];
    EffectVector3_00445620 base;      // +0x334
    EffectVector3_00445620 position;  // +0x340
    unsigned char unknown_34C[0x358 - 0x34C];
    EffectState_00445620* state;               // +0x358

    __declspec(noinline) int Advance();
};

#pragma code_seg(".text$02effectring")
int EffectEntity_00445620::Advance() {
    EffectState_00445620* state = this->state;
    EffectParticle_00445620* ring = state->particles;
    ring[0].position = base + position;

    float angle = -3.14159265358979323846f;

    ring[0].countdown_a += state->rate;
    if (ring[0].countdown_a < 0.0f) state->RaiseCountdownA();
    ring[0].countdown_b += state->rate;
    if (ring[0].countdown_b < 0.0f) state->RaiseCountdownB();
    ring[0].color = color;

    EffectParticle_00445620* first = &ring[1];
    EffectParticle_00445620* particle = first;
    int index = 0;
    do {
        particle->countdown_a += state->rate;
        if (particle->countdown_a < 0.0f) state->RaiseCountdownA();
        particle->countdown_b += state->Rate();
        if (particle->countdown_b < 0.0f) state->RaiseCountdownB();
        particle->color = color;
        ((unsigned char*)&particle->color)[3] = 0;
        state->radii_a[index] += state->RadiusStep(index);
        ((Vector2_004458b0*)particle)->SetPolar(angle, state->radii_a[index]);
        particle->position += base + position;
        angle += 0.20268340408802032f;
        ++particle;
    } while (++index < 0x1F);

    *particle = *first;
    return 0;
}
#pragma code_seg()
