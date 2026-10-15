#pragma once
#include <stddef.h>
#include <string.h>
struct ReplayPool;
struct ReplayPoolLink_0042aa50 {
    ReplayPool* pool;
    ReplayPoolLink_0042aa50* next;
    ReplayPoolLink_0042aa50* previous;
    void InsertAfter(ReplayPoolLink_0042aa50* position) {
        if (position->next) {
            next = position->next;
            position->next->previous = this;
        }
        position->next = this;
        previous = position;
    }
};
// The replay writer stores three 16-bit values per input record.
struct ReplayInputRecord {
    unsigned short buttons;
    unsigned short value_02;
    unsigned short value_04;
};
struct ReplayPool {
    ReplayInputRecord input_records[3600]; // +0x0000
    ReplayInputRecord* input_cursor;      // +0x5460
    unsigned char state_records[3600];          // +0x5464
    unsigned char* state_cursor;                 // +0x6274
    ReplayPoolLink_0042aa50 link;                 // +0x6278
    ReplayPool() {
        memset(this, 0, sizeof(*this));
        input_cursor = input_records;
        state_cursor = state_records;
        link.pool = this;
        link.next = 0;
        link.previous = 0;
    }
};
struct ReplayPoolLists {
    unsigned char reserved_00[0x3C];
    ReplayPoolLink_0042aa50 stages[8];
};
typedef char ReplayInputRecordSize[sizeof(ReplayInputRecord)==6?1:-1];
typedef char ReplayInputCursorOffset[offsetof(ReplayPool,input_cursor)==0x5460?1:-1];
typedef char ReplayStateRecordsOffset[offsetof(ReplayPool,state_records)==0x5464?1:-1];
typedef char ReplayStateCursorOffset[offsetof(ReplayPool,state_cursor)==0x6274?1:-1];
typedef char ReplayStageListsOffset[offsetof(ReplayPoolLists,stages)==0x3C?1:-1];
typedef char ReplayStageListsSize[sizeof(ReplayPoolLists)==0x9C?1:-1];
typedef char ReplayPoolSize[sizeof(ReplayPool)==0x6284?1:-1];
typedef char ReplayPoolLinkOffset[offsetof(ReplayPool,link)==0x6278?1:-1];
extern "C" __declspec(noinline) ReplayPoolLink_0042aa50* __stdcall
ReplayPool_AllocateAndAppend(int stage, ReplayPoolLists* lists);
