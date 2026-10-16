#pragma once

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// The 0x37B0-byte spell-card manager, as far as its factory touches it.
struct Card3 {
    unsigned char reserved_0000[0x37B0 - 0x488];
    unsigned char tail[0x488];

    __declspec(noinline) Card3();     // 0x00408910
    __declspec(noinline) ~Card3();    // 0x00408AF0
    // 0x004089C0: register its tasks and reset its frame timer; nonzero on failure.
    __declspec(noinline) int Initialize();
};
typedef char CardSize3[sizeof(Card3) == 0x37B0 ? 1 : -1];

__declspec(noinline) Card3* __stdcall Card_Create2();
