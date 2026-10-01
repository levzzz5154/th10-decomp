#pragma once
#include <string.h>
#include <stddef.h>

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// One 0x24-byte list node of the replay manager; built by 0x0042AC20 and
// unlinked by 0x0042AC60.
struct ReplayManagerNode_004296f0 {
    unsigned char storage[0x24];

    __declspec(noinline) ReplayManagerNode_004296f0();
    __declspec(noinline) ~ReplayManagerNode_004296f0();
};

// The 0x2D4-byte replay manager, as far as its factory touches it.
struct ReplayManager_004296f0 {
    unsigned char reserved_000[0x10];
    int mode;                               // 0 = record, 1 = play back, 2 = file opened directly
    unsigned char reserved_014[0xA0 - 0x14];
    ReplayManagerNode_004296f0 nodes[8];
    unsigned char reserved_1c0[0x1D4 - 0x1C0];
    char path[0x100];

    ReplayManager_004296f0() { memset(this, 0, sizeof(*this)); }
    __declspec(noinline) ~ReplayManager_004296f0();    // 0x004294A0
    // 0x0042A200: remember the replay file's path and read it; nonzero on failure.
    __declspec(noinline) int Initialize(const char* replay_path);
    // 0x00428F60: start recording (mode 0) or play back the named replay
    // (mode 1); nonzero on failure.
    __declspec(noinline) int Start(int start_mode, const char* replay_path);
};
typedef char ReplayManagerSize_004296f0[sizeof(ReplayManager_004296f0) == 0x2D4 ? 1 : -1];
typedef char ReplayManagerNodes_004296f0[offsetof(ReplayManager_004296f0, nodes) == 0xA0 ? 1 : -1];

__declspec(noinline) ReplayManager_004296f0* __stdcall ReplayManager_Create_004296f0(const char* replay_path);
__declspec(noinline) ReplayManager_004296f0* __stdcall ReplayManager_Create_00429610(int start_mode, const char* replay_path);
