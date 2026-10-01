#pragma once

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// The 0x37B0-byte player manager, as far as its factory touches it.
struct PlayerManager_00408c90 {
    unsigned char reserved_0000[0x37B0 - 0x488];
    unsigned char tail[0x488];

    __declspec(noinline) PlayerManager_00408c90();     // 0x00408910
    __declspec(noinline) ~PlayerManager_00408c90();    // 0x00408AF0
    // 0x004089C0: register its tasks and reset its frame timer; nonzero on failure.
    __declspec(noinline) int Initialize();
};
typedef char PlayerManagerSize_00408c90[sizeof(PlayerManager_00408c90) == 0x37B0 ? 1 : -1];

__declspec(noinline) PlayerManager_00408c90* __stdcall PlayerManager_Create_00408c90();
