#pragma once
#include <stddef.h>

// Shared layout for the 31-entry request/resource table.
struct MusicCommand {
    int resource;
    int parameter;
    int state;
    char name[0x100];
};
struct WaveSoundManager {
    unsigned char reserved_000[0x1F88];
    MusicCommand records[31];
    __declspec(noinline) char* QueueMusicCommand(const char* name, int resource, int parameter);
};
typedef char RegistrarOffsetCheck[(offsetof(WaveSoundManager, records) == 0x1F88) ? 1 : -1];
typedef char RegistrarStrideCheck[(sizeof(MusicCommand) == 0x10C) ? 1 : -1];
