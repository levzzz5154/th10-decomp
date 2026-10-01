#pragma once
#include <stddef.h>

struct MusicRecord {
    unsigned char name[16];
    unsigned int offset;                 // +0x10: offset within the music file
    unsigned int data_bytes;             // +0x14
    int start;                           // +0x18: optional signed loop start
    int end;                             // +0x1c: signed loop end
    unsigned char format[14];            // +0x20: first WAVEFORMAT fields
    unsigned short bits;                 // +0x2e: bits per sample
};

struct MusicCursor {
    unsigned char reserved[8];
    unsigned int remaining;              // +0x08: remaining file bytes
    unsigned char reserved0c[0x70];
    unsigned int buffered;               // +0x7c: nonzero selects memory mode
    unsigned char* base;                 // +0x80
    unsigned char* position;             // +0x84
    unsigned int memory_end;             // +0x88: relative to base
    void* file;                          // +0x8c
    MusicRecord* record;                 // +0x90
};

struct WaveBuffer;
struct WaveMethods {
    int (__stdcall* query_interface)(WaveBuffer*, const void* iid, void** object); // +0x00
    void* add_ref;
    unsigned int (__stdcall* release)(WaveBuffer*);                  // +0x08
    void* reserved0c[6];
    int (__stdcall* get_status)(WaveBuffer*, unsigned int*); // +0x24
    void* reserved28;
    int (__stdcall* lock)(              // +0x2c
        WaveBuffer*, unsigned int, unsigned int,
        unsigned char**, unsigned int*, unsigned char**, unsigned int*,
        unsigned int);
    void* reserved30;
    int (__stdcall* set_current_position)(WaveBuffer*, unsigned int); // +0x34
    void* reserved38[5];
    int (__stdcall* unlock)(            // +0x4c
        WaveBuffer*, unsigned char*, unsigned int, unsigned char*, unsigned int);
    int (__stdcall* restore)(WaveBuffer*); // +0x50
};
struct WaveBuffer {
    WaveMethods* methods;
};
struct SoundStream {
    void* methods;
    WaveBuffer** buffers;               // +0x04
    unsigned int buffer_bytes;          // +0x08
    MusicCursor* reader;                // +0x0c
};

// The sound device: creates the buffers a stream plays through.
struct SoundDevice;
struct SoundDeviceMethods {
    void* reserved00[3];
    int (__stdcall* create_sound_buffer)(SoundDevice*, const void* description,
        WaveBuffer** buffer, void* outer);                           // +0x0C
};
struct SoundDevice {
    SoundDeviceMethods* methods;
};
struct SoundDeviceOwner {
    SoundDevice* device;
};

// A buffer's play-position notifications.
struct SoundNotifyPosition {
    unsigned int offset;
    void* event;
};
struct SoundNotify;
struct SoundNotifyMethods {
    void* query_interface;
    void* add_ref;
    unsigned int (__stdcall* release)(SoundNotify*);                 // +0x08
    int (__stdcall* set_notification_positions)(SoundNotify*, unsigned int count,
        const SoundNotifyPosition* positions);                       // +0x0C
};
struct SoundNotify {
    SoundNotifyMethods* methods;
};

// The whole streaming sound.
struct SoundStreamState : SoundStream {
    unsigned int buffer_count;          // +0x10
    unsigned char reserved_14[0x30 - 0x14];
    unsigned int last_play_position;    // +0x30
    unsigned char buffer_description[0x24];     // +0x34
    SoundDeviceOwner* owner;            // +0x58
    unsigned char reserved_5c[0x6C - 0x5C];
    unsigned int notify_bytes;          // +0x6C
    void* notify_event;                 // +0x70
};
typedef char LayoutOwner[offsetof(SoundStreamState, owner) == 0x58 ? 1 : -1];

typedef void (__stdcall* StreamSleep)(unsigned int);
extern "C" {
    extern StreamSleep data_004660ac;
    extern unsigned int data_004977a4;
    extern unsigned int (__stdcall* data_004660c8)(
        void*, int, int*, unsigned int);
    __declspec(dllimport) int __stdcall ReadFile(
        void*, void*, unsigned int, unsigned int*, void*);
}
extern "C" __declspec(noinline) int __stdcall ArchiveRead(
    MusicCursor*, unsigned int, unsigned int, unsigned int*);
extern "C" __declspec(noinline) int __stdcall ArchiveRewind(MusicCursor*, bool);

typedef char LayoutOffset[offsetof(MusicRecord, offset) == 0x10 ? 1 : -1];
typedef char LayoutStart[offsetof(MusicRecord, start) == 0x18 ? 1 : -1];
typedef char LayoutEnd[offsetof(MusicRecord, end) == 0x1c ? 1 : -1];
typedef char LayoutBits[offsetof(MusicRecord, bits) == 0x2e ? 1 : -1];
typedef char LayoutRemaining[offsetof(MusicCursor, remaining) == 8 ? 1 : -1];
typedef char LayoutBuffered[offsetof(MusicCursor, buffered) == 0x7c ? 1 : -1];
typedef char LayoutBase[offsetof(MusicCursor, base) == 0x80 ? 1 : -1];
typedef char LayoutPosition[offsetof(MusicCursor, position) == 0x84 ? 1 : -1];
typedef char LayoutMemoryEnd[offsetof(MusicCursor, memory_end) == 0x88 ? 1 : -1];
typedef char LayoutFile[offsetof(MusicCursor, file) == 0x8c ? 1 : -1];
typedef char LayoutRecord[offsetof(MusicCursor, record) == 0x90 ? 1 : -1];
typedef char LayoutReader[offsetof(SoundStream, reader) == 0x0c ? 1 : -1];
typedef char LayoutStatus[offsetof(WaveMethods, get_status) == 0x24 ? 1 : -1];
typedef char LayoutLock[offsetof(WaveMethods, lock) == 0x2c ? 1 : -1];
typedef char LayoutUnlock[offsetof(WaveMethods, unlock) == 0x4c ? 1 : -1];
typedef char LayoutSetPosition[offsetof(WaveMethods, set_current_position) == 0x34 ? 1 : -1];
typedef char LayoutRestore[offsetof(WaveMethods, restore) == 0x50 ? 1 : -1];
