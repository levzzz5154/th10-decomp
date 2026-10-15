#pragma once
#include <stddef.h>

// Shared layout for the 31-entry request/resource table.
struct AnimationResourceRecord {
    int resource;
    int parameter;
    int state;
    char name[0x100];
};
struct AnimationManager_0043e460 {
    unsigned char reserved_000[0x1F88];
    AnimationResourceRecord records[31];
    __declspec(noinline) char* RegisterResource(const char* name, int resource, int parameter);
};
typedef char RegistrarOffsetCheck[(offsetof(AnimationManager_0043e460, records) == 0x1F88) ? 1 : -1];
typedef char RegistrarStrideCheck[(sizeof(AnimationResourceRecord) == 0x10C) ? 1 : -1];
