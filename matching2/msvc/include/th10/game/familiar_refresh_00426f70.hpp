#pragma once
#include <stddef.h>
#include "th10/game/card_animations.hpp"
#include "th10/render/animation_stop_frame_handle.hpp"

// View of the player runtime used by the familiar refresh at 0x00426F70.
//
// The four familiar records sit at player +0x32A0 with a 0x98 stride (the
// trail sprite callback at 0x00427950 sees the same record: position at
// +0x34, offset at +0x44, index at +0x88).  Each record carries its activity
// state, its on-screen position and anchor, the unfocused and focused
// offsets from the shot schedule, the orbit and attached-effect animation
// handles, its index, a dirty flag and the scheduler callback.
struct FamiliarPoint {
    int x, y;
    FamiliarPoint() {}
    FamiliarPoint(int px, int py) : x(px), y(py) {}
    void CopyFrom(const FamiliarPoint& other) { x = other.x; y = other.y; }
    FamiliarPoint operator+(const FamiliarPoint& other) const {
        return FamiliarPoint(x + other.x, y + other.y);
    }
};

typedef int (__fastcall* FamiliarCallback)(void* record);

struct FamiliarRecord {
    int state;                               // +0x00: 0 idle, 2 active
    unsigned char reserved_04[0x34 - 0x04];
    FamiliarPoint position;         // +0x34
    FamiliarPoint anchor;           // +0x3C
    FamiliarPoint carried;          // +0x44: unfocused offset
    FamiliarPoint focused;          // +0x4C: focused offset
    unsigned char reserved_54[0x68 - 0x54];
    int handle;                              // +0x68: orbit animation
    int effect_handle;                       // +0x6C: attached effect
    unsigned char reserved_70[0x88 - 0x70];
    int index;                               // +0x88
    int dirty;                               // +0x8C
    FamiliarCallback callback;      // +0x90
    unsigned char reserved_94[0x98 - 0x94];
};

typedef char FamiliarRecordSize[
    sizeof(FamiliarRecord) == 0x98 ? 1 : -1];

// The registered animation objects behind the handles.  Bucket nodes alias
// the object's script-id word; children propagate marks when unflagged.
struct FamiliarAnimObject;          // the registered Entity

struct FamiliarAnimEntry {
    FamiliarAnimObject* object;     // +0x00 registered object
    FamiliarAnimEntry* next;        // +0x04 bucket list link
};

struct FamiliarAnimObject {
    int animation_handle;                    // +0x000
    unsigned char reserved_004[0x14 - 0x04];
    FamiliarAnimEntry* children;    // +0x014 child node list
    int children_flagged;                    // +0x018 children already marked
    unsigned char reserved_01c[0x304 - 0x01C];
    unsigned short stop_frame;               // +0x304 stop state word
    unsigned char reserved_306[0x35C - 0x306];
    unsigned int flags;                      // +0x35C removal/flag bits
};

struct FamiliarAnimManager {
    unsigned char reserved_000000[0x72DAD4];
    FamiliarAnimEntry* primary_head;    // +0x72DAD4
    unsigned char reserved_dad8[4];
    FamiliarAnimEntry* secondary_head;  // +0x72DADC
};

// The shot schedule table the player runtime points at (+0x45C): 12-byte
// rows; row k's unfocused offset lives at +0x20 and its focused offset ten
// rows later (+0x98).  Volatile preserves the retail x87 operand order
// (fld [row], fmul [scaler]) under the whole-program pass.
struct FamiliarOffsetRow {
    volatile float x, y, z;
};

struct FamiliarOffsetTable {
    unsigned char reserved_00[0x20];
    union {
        FamiliarOffsetRow carried[26];  // +0x20
        struct {
            FamiliarOffsetRow overlay_pad[10];
            FamiliarOffsetRow focused[26];  // +0x98
        };
    };
};

struct PlayerFamiliarRuntime {
    unsigned char reserved_0000[0x10];
    AnimationBank* resource;        // +0x010
    unsigned char reserved_0014[0x3CC - 0x14];
    FamiliarPoint anchor;               // +0x3CC
    unsigned char reserved_03d4[0x45C - 0x3D4];
    const FamiliarOffsetTable* offsets; // +0x45C
    unsigned char reserved_0460[0x32A0 - 0x460];
    FamiliarRecord familiars[4];        // +0x32A0
    int familiar_count;                          // +0x3500: applied count
    unsigned char reserved_3504[0x436C - 0x3504];
    FamiliarPoint history[33];          // +0x436C
    int alternate;                               // +0x4474
};

// The running game's counters at 0x00474C44 (one object whose address is
// taken elsewhere, so stores through pointers make the compiler reload it).
struct FamiliarGameCounters {
    int score;                                   // 0x00474C44
    short power;                                 // 0x00474C48
    unsigned char reserved_06[0x24 - 0x06];
    int character;                               // 0x00474C68
    int shot_type;                               // 0x00474C6C
};

extern "C" FamiliarGameCounters g_globals_score;
