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
    void* reserved00[9];
    int (__stdcall* get_status)(WaveBuffer*, unsigned int*); // +0x24
    void* reserved28;
    int (__stdcall* lock)(              // +0x2c
        WaveBuffer*, unsigned int, unsigned int,
        unsigned char**, unsigned int*, unsigned char**, unsigned int*,
        unsigned int);
    int (__stdcall* play)(WaveBuffer*, unsigned int, unsigned int, unsigned int);
    int (__stdcall* set_position)(WaveBuffer*, unsigned int);
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
    unsigned int count;
    unsigned int fade_remaining;
    unsigned int fade_duration;
    unsigned int fade_mode;
    unsigned int play_priority;
    unsigned int play_flags;
    unsigned int unknown28;
    unsigned int unknown2c;
    unsigned int playing;
};

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
typedef char LayoutRestore[offsetof(WaveMethods, restore) == 0x50 ? 1 : -1];

// 0x0044D300 - Query an interface and restore it until it is ready.
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


// 0x0044D370 - Select the first idle interface, or a random fallback.
// The native matched expression below permits Clang to read entries_004
// before rand. Explicitly sequenced candidate and differential evidence:
// reference/semantic_candidates/sound_stream_select.cpp and
// reference/recovery_notes/sound_stream_start_0044d440.md.
extern "C" int __cdecl asm_rand_0045371b();

struct PlatformD370Entry {
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
};

struct PlatformInterfaceState_0044D370 {
    unsigned char unknown_000[4];
    void** entries_004;
    unsigned char unknown_008[8];
    unsigned int count_010;

    __declspec(noinline) PlatformD370Entry* FindAvailable();
};


// 0x0044D600 - Rewind each DirectSound buffer with SetCurrentPosition(0),
// combining their HRESULTs with OR. The historical Query name is retained.
// Native LTCG gives this member's internal receiver convention: the state
// arrives in EDI and the result is returned in EAX.
typedef int (__stdcall *RecoveryLeafD600Query)(void*, unsigned int);

struct PlatformQueryInterfaces {
    unsigned char unknown_000[4];
    void** entries_004;
    unsigned char unknown_008[8];
    unsigned int count_010;

    __declspec(noinline) int Query();
};


#include "th10/platform/sound_fade_0044d4e0.hpp"
extern "C" __declspec(noinline) int __stdcall SoundStreamFill(SoundStream*, WaveBuffer*, unsigned int);

// Additional start layout contracts, pinned to the retail PE32 target.
typedef char SoundStartOffset_count[offsetof(SoundStream, count) == 0x10 ? 1 : -1];
typedef char SoundStartOffset_fade_remaining[offsetof(SoundStream, fade_remaining) == 0x14 ? 1 : -1];
typedef char SoundStartOffset_fade_duration[offsetof(SoundStream, fade_duration) == 0x18 ? 1 : -1];
typedef char SoundStartOffset_fade_mode[offsetof(SoundStream, fade_mode) == 0x1c ? 1 : -1];
typedef char SoundStartOffset_play_priority[offsetof(SoundStream, play_priority) == 0x20 ? 1 : -1];
typedef char SoundStartOffset_play_flags[offsetof(SoundStream, play_flags) == 0x24 ? 1 : -1];
typedef char SoundStartOffset_unknown2c[offsetof(SoundStream, unknown2c) == 0x2c ? 1 : -1];
typedef char SoundStartOffset_playing[offsetof(SoundStream, playing) == 0x30 ? 1 : -1];
typedef char SoundStartMethod_play[offsetof(WaveMethods, play) == 0x30 ? 1 : -1];
typedef char SoundStartMethod_set_position[offsetof(WaveMethods, set_position) == 0x34 ? 1 : -1];
