#pragma once
#include <stddef.h>
#include <string.h>

struct RecorderKeyRepeatState {
    unsigned int raw_keys;                 // +0x00
    unsigned short pressed;                // +0x04
    unsigned char reserved_06[0x2A - 6];
    unsigned short held_frames;            // +0x2A
    union {
        struct {
            unsigned short held_keys;      // +0x2C
            unsigned short previous_keys;  // +0x2E
        };
        unsigned int input_word;           // +0x2C, same four bytes
    };
    unsigned short repeat_flags;           // +0x30
    unsigned short new_press;              // +0x32
    unsigned short new_release;            // +0x34
    unsigned short reserved_36;
    unsigned short repeat_counters[16];    // +0x38
    __declspec(noinline) unsigned short Update();
};

struct RecorderInputRecord {
    unsigned short buttons;
    unsigned short value_02;
    unsigned short value_04;
};

struct RecorderPool;
struct RecorderPoolLink {
    RecorderPool* pool;
    RecorderPoolLink* next;
    RecorderPoolLink* previous;
};

// The structural constructor matches the existing complete append-page model,
// while its first pointer is named as the actual moving input cursor.
struct RecorderPoolStorage {
    RecorderInputRecord* input_cursor;
    unsigned char state_records[3600];
    unsigned char* state_cursor;
    void Attach(RecorderInputRecord* begin) {
        input_cursor = begin;
        state_cursor = state_records;
    }
};

struct RecorderPool {
    RecorderInputRecord input_records[3600]; // +0x0000
    RecorderPoolStorage storage;            // +0x5460
    RecorderPoolLink link;                  // +0x6278
    RecorderPool() {
        memset(this, 0, sizeof(*this));
        storage.Attach(input_records);
        link.pool = this;
        link.next = 0;
        link.previous = 0;
    }
    __declspec(noinline) int AppendPacket(
        unsigned short first, unsigned short second, unsigned short third);
};

struct RecorderPoolLists {
    unsigned char reserved_00[0x3C];
    RecorderPoolLink stages[8];             // +0x3C
    __declspec(noinline) RecorderPoolLink* AppendPage(int stage);
};

typedef char RecorderKeyRepeatSize[sizeof(RecorderKeyRepeatState)==0x58?1:-1];
typedef char RecorderHoldOffset[offsetof(RecorderKeyRepeatState,held_frames)==0x2A?1:-1];
typedef char RecorderHeldOffset[offsetof(RecorderKeyRepeatState,held_keys)==0x2C?1:-1];
typedef char RecorderInputWordOffset[offsetof(RecorderKeyRepeatState,input_word)==0x2C?1:-1];
typedef char RecorderPreviousOffset[offsetof(RecorderKeyRepeatState,previous_keys)==0x2E?1:-1];
typedef char RecorderCounterOffset[offsetof(RecorderKeyRepeatState,repeat_counters)==0x38?1:-1];
typedef char RecorderInputRecordSize[sizeof(RecorderInputRecord)==6?1:-1];
typedef char RecorderPoolStorageOffset[offsetof(RecorderPool,storage)==0x5460?1:-1];
typedef char RecorderInputCursorOffset[offsetof(RecorderPool,storage)+offsetof(RecorderPoolStorage,input_cursor)==0x5460?1:-1];
typedef char RecorderStateRecordsOffset[offsetof(RecorderPool,storage)+offsetof(RecorderPoolStorage,state_records)==0x5464?1:-1];
typedef char RecorderStateCursorOffset[offsetof(RecorderPool,storage)+offsetof(RecorderPoolStorage,state_cursor)==0x6274?1:-1];
typedef char RecorderPoolLinkOffset[offsetof(RecorderPool,link)==0x6278?1:-1];
typedef char RecorderPoolSize[sizeof(RecorderPool)==0x6284?1:-1];
typedef char RecorderStageOffset[offsetof(RecorderPoolLists,stages)==0x3C?1:-1];
typedef char RecorderStageOwnerSize[sizeof(RecorderPoolLists)==0x9C?1:-1];

void* __cdecl operator new(unsigned int size);
extern "C" RecorderKeyRepeatState g_input_keys_raw;
