#pragma once

// First DirectSound buffer of the platform sound state and its volume fades.
extern "C" int data_00497854;

struct PlatformD4E0Entry {
    virtual void __stdcall slot_00() = 0;
    virtual void __stdcall slot_04() = 0;
    virtual void __stdcall slot_08() = 0;
    virtual void __stdcall slot_0c() = 0;
    virtual void __stdcall slot_10() = 0;
    virtual void __stdcall slot_14() = 0;
    virtual void __stdcall slot_18() = 0;
    virtual void __stdcall slot_1c() = 0;
    virtual void __stdcall slot_20() = 0;
    virtual void __stdcall slot_24() = 0;
    virtual void __stdcall slot_28() = 0;
    virtual void __stdcall slot_2c() = 0;
    virtual void __stdcall slot_30() = 0;
    virtual void __stdcall slot_34() = 0;
    virtual void __stdcall slot_38() = 0;
    virtual int __stdcall set_deadline(int) = 0;   // +0x3C: SetVolume
    virtual void __stdcall slot_40() = 0;
    virtual void __stdcall slot_44() = 0;
    virtual int __stdcall stop() = 0;              // +0x48: Stop
};

struct PlatformInterfaceState_0044D4E0 {
    unsigned char unknown_000[4];
    PlatformD4E0Entry** entries_004;
    unsigned char unknown_008[0xC];
    int fade_remaining_014;             // frames left in the running fade
    int fade_length_018;                // total frames of the running fade
    int fade_mode_01c;                  // 0 idle, 1..4 the fade kind

    __declspec(noinline) int SetOperationDeadline(int deadline);
    // 0x0044D740..0x0044D810: one frame of each fade kind; each returns 1 on
    // the frame the fade finishes.
    int FadeOutAndStop();
    int FadeDownHalf();
    int FadeDownSlight();
    int FadeUpSlight();
};
