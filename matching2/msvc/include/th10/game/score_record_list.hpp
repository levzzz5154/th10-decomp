#pragma once
#include <stddef.h>

// Score records use virtual callbacks and a sentinel predecessor link.
struct ScoreLinkedRecord_0041c480 {
    virtual void Reserved0();
    virtual void Reserved4();
    virtual int Update();                // dispatch slot +0x08
    virtual void ReservedC();
    virtual void Destroy();              // dispatch slot +0x10

    ScoreLinkedRecord_0041c480* prev;     // +0x04
    ScoreLinkedRecord_0041c480* next;     // +0x08
    int state;                           // +0x0C
    int previous;                        // +0x10
    int current;                         // +0x14
    float elapsed;                       // +0x18
    const float* speed;                  // +0x1C
    unsigned char reserved_020[0x30];
    unsigned char retire_count;          // +0x50
};

struct ScoreRecords_0041c480 {
    unsigned char pad_000[0x18];
    ScoreLinkedRecord_0041c480* head;     // +0x18
    unsigned char pad_01C[0x418];
    ScoreLinkedRecord_0041c480* cursor;   // +0x434
    int live_count;                      // +0x438

    __declspec(noinline) int AdvanceFrame();
};

typedef char ScoreRecords_head_offset[(offsetof(ScoreRecords_0041c480, head) == 0x18) ? 1 : -1];
typedef char ScoreRecords_cursor_offset[(offsetof(ScoreRecords_0041c480, cursor) == 0x434) ? 1 : -1];
typedef char ScoreRecords_live_count_offset[(offsetof(ScoreRecords_0041c480, live_count) == 0x438) ? 1 : -1];

// 0x0041C330: update every record and retire the finished ones; returns 1.
// Its one caller passes the records in EDI.
extern "C" int __cdecl ScoreRecords_Tick_0041c330(ScoreRecords_0041c480* records);
