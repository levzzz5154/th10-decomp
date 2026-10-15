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
    unsigned char reserved0c[0x20];
    unsigned int total_pcm_bytes;        // +0x2c
    unsigned char reserved30[0x4c];
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
    void* reserved0c;
    int (__stdcall* get_position)(WaveBuffer*, unsigned int*, unsigned int*); // +0x10
    void* reserved14[4];
    int (__stdcall* get_status)(WaveBuffer*, unsigned int*); // +0x24
    void* reserved28;
    int (__stdcall* lock)(              // +0x2c
        WaveBuffer*, unsigned int, unsigned int,
        unsigned char**, unsigned int*, unsigned char**, unsigned int*,
        unsigned int);
    void* reserved30;
    int (__stdcall* set_current_position)(WaveBuffer*, unsigned int); // +0x34
    void* reserved38[4];
    int (__stdcall* stop)(WaveBuffer*); // +0x48
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

// Fields shared with the initial-fill model, followed by notification state.
struct SoundStreamState : SoundStream {
    unsigned char reserved10[0x5c - 0x10];
    unsigned int previous_play_position; // +0x5c
    unsigned int played_bytes;           // +0x60
    unsigned int write_offset;           // +0x64
    unsigned int end_of_stream;          // +0x68
    unsigned int notify_bytes;           // +0x6c
    void* notify_event;                  // +0x70
    unsigned int servicing;             // +0x74
};
typedef char LayoutPreviousPlay[offsetof(SoundStreamState, previous_play_position) == 0x5c ? 1 : -1];
typedef char LayoutPlayed[offsetof(SoundStreamState, played_bytes) == 0x60 ? 1 : -1];
typedef char LayoutWrite[offsetof(SoundStreamState, write_offset) == 0x64 ? 1 : -1];
typedef char LayoutEnded[offsetof(SoundStreamState, end_of_stream) == 0x68 ? 1 : -1];
typedef char LayoutNotifyBytes[offsetof(SoundStreamState, notify_bytes) == 0x6c ? 1 : -1];
typedef char LayoutStreamSize[sizeof(SoundStreamState) == 0x78 ? 1 : -1];

typedef void (__stdcall* StreamSleep)(unsigned int);
extern "C" {
    extern StreamSleep imp_Sleep;
    extern unsigned int g_bgm_data_offset;
    extern unsigned int (__stdcall* imp_SetFilePointer)(
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

// Native 0x0044D300 helper view: query status and restore a lost buffer.
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned int);

struct PlatformD300Entry {
    virtual void __stdcall slot_00() = 0;
    virtual void __stdcall slot_04() = 0;
    virtual void __stdcall slot_08() = 0;
    virtual void __stdcall slot_0c() = 0;
    virtual void __stdcall slot_10() = 0;
    virtual void __stdcall slot_14() = 0;
    virtual void __stdcall slot_18() = 0;
    virtual void __stdcall slot_1c() = 0;
    virtual void __stdcall slot_20() = 0;
    virtual int __stdcall read_state(unsigned int*) = 0;
    virtual void __stdcall slot_28() = 0;
    virtual void __stdcall slot_2c() = 0;
    virtual void __stdcall slot_30() = 0;
    virtual void __stdcall slot_34() = 0;
    virtual void __stdcall slot_38() = 0;
    virtual void __stdcall slot_3c() = 0;
    virtual void __stdcall slot_40() = 0;
    virtual void __stdcall slot_44() = 0;
    virtual void __stdcall slot_48() = 0;
    virtual void __stdcall slot_4c() = 0;
    virtual int __stdcall restore() = 0;

    __declspec(noinline) int Run(unsigned int* completed);
};

typedef char LayoutTotalPcm[offsetof(MusicCursor, total_pcm_bytes) == 0x2c ? 1 : -1];
typedef char LayoutGetPosition[offsetof(WaveMethods, get_position) == 0x10 ? 1 : -1];
typedef char LayoutStop[offsetof(WaveMethods, stop) == 0x48 ? 1 : -1];
