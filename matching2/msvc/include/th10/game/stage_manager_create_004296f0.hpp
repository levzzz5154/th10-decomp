#pragma once
#include <string.h>
#include <stddef.h>

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// One 0x24-byte list node of the stage manager; built by 0x0042AC20 and
// unlinked by 0x0042AC60.
struct StageManagerNode_004296f0 {
    unsigned char storage[0x24];

    __declspec(noinline) StageManagerNode_004296f0();
    __declspec(noinline) ~StageManagerNode_004296f0();
};

// The 0x2D4-byte stage manager, as far as its factory touches it.
struct StageManager_004296f0 {
    unsigned char reserved_000[0x10];
    int mode;                               // 2 once created
    unsigned char reserved_014[0xA0 - 0x14];
    StageManagerNode_004296f0 nodes[8];
    unsigned char reserved_1c0[0x1D4 - 0x1C0];
    char path[0x100];

    StageManager_004296f0() { memset(this, 0, sizeof(*this)); }
    __declspec(noinline) ~StageManager_004296f0();    // 0x004294A0
    // 0x0042A200: remember the stage file's path and load it; nonzero on failure.
    __declspec(noinline) int Initialize(const char* stage_path);
};
typedef char StageManagerSize_004296f0[sizeof(StageManager_004296f0) == 0x2D4 ? 1 : -1];
typedef char StageManagerNodes_004296f0[offsetof(StageManager_004296f0, nodes) == 0xA0 ? 1 : -1];

__declspec(noinline) StageManager_004296f0* __stdcall StageManager_Create_004296f0(const char* stage_path);
