#pragma once

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// The 0x9ED0-byte item manager, as far as its factory touches it. Six pools of
// 0x3AC-byte sprites start at +0x10; the trailing state starts at +0x9A48.
struct Hud {
    unsigned char reserved_0000[0x9A48];
    unsigned char tail[0x9ED0 - 0x9A48];

    __declspec(noinline) Hud();     // 0x00413810
    __declspec(noinline) ~Hud();    // 0x004145F0
    // 0x00413980: load its resources and register its tasks; nonzero on failure.
    __declspec(noinline) int Initialize();
};
typedef char ItemManagerSize_00414830[sizeof(Hud) == 0x9ED0 ? 1 : -1];

__declspec(noinline) Hud* __stdcall Hud_Create();
