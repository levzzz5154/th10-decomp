#pragma once

struct MovementPair_0041ab70 {
    int x;
    int y;
};

struct EntityMovementSlot_0041ab70 {
    unsigned char reserved_000[0x180];
    MovementPair_0041ab70 source;
    MovementPair_0041ab70 destination;
    unsigned char reserved_190[0x10];
    int timer;
    int previous;
    int elapsed;
    const float* speed;
    unsigned int flags;
    int mode;
    int interpolation;

    __declspec(noinline) void Initialise(const MovementPair_0041ab70* source_value,
                                         const MovementPair_0041ab70* destination_value,
                                         int mode_value, unsigned char interpolation_value);
};
