#pragma once

struct MovementPair {
    int x;
    int y;
};

struct EntityMovementSlot {
    unsigned char reserved_000[0x180];
    MovementPair source;
    MovementPair destination;
    unsigned char reserved_190[0x10];
    int timer;
    int previous;
    int elapsed;
    const float* speed;
    unsigned int flags;
    int mode;
    int interpolation;

    __declspec(noinline) void Initialise(const MovementPair* source_value,
                                         const MovementPair* destination_value,
                                         int mode_value, unsigned char interpolation_value);
};
