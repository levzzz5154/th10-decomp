#pragma once


// 0x0044D080 - release everything the owned-array object holds: every interface
// in the owned array, the array itself, and the playback device. The object
// returns to the base table at 0x004705D8 first.
//
// th10/platform/sound_buffer.hpp names only the vtable prefix that the
// sound-buffer leaves touch, so the complete layout used here is declared
// locally.
struct OwnedInterface {
    virtual unsigned long __stdcall QueryInterface(void* id, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct OwnedPlaybackDevice {
    unsigned int reserved_00[0x1E];   // +0x00..+0x77
    unsigned int state;               // +0x78, one while the handle is owned
    unsigned int reserved_7C[4];      // +0x7C..+0x8B
    HANDLE handle;                    // +0x8C
};

struct PlatformOwnedArrayFields {
    void* vtable;                     // +0x00
    OwnedInterface** elements;        // +0x04, owned interface pointers
    unsigned int reserved_08;         // +0x08
    OwnedPlaybackDevice* device;      // +0x0C, owned playback device
    unsigned int element_count;       // +0x10
};

