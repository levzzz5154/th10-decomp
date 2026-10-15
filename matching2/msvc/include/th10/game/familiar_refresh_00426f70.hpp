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
struct FamiliarPoint_00426f70 {
    int x, y;
    FamiliarPoint_00426f70() {}
    FamiliarPoint_00426f70(int px, int py) : x(px), y(py) {}
    void CopyFrom(const FamiliarPoint_00426f70& other) { x = other.x; y = other.y; }
    FamiliarPoint_00426f70 operator+(const FamiliarPoint_00426f70& other) const {
        return FamiliarPoint_00426f70(x + other.x, y + other.y);
    }
};

typedef int (__fastcall* FamiliarCallback_00426f70)(void* record);

struct FamiliarRecord_00426f70 {
    int state;                               // +0x00: 0 idle, 2 active
    unsigned char reserved_04[0x34 - 0x04];
    FamiliarPoint_00426f70 position;         // +0x34
    FamiliarPoint_00426f70 anchor;           // +0x3C
    FamiliarPoint_00426f70 carried;          // +0x44: unfocused offset
    FamiliarPoint_00426f70 focused;          // +0x4C: focused offset
    unsigned char reserved_54[0x68 - 0x54];
    int handle;                              // +0x68: orbit animation
    int effect_handle;                       // +0x6C: attached effect
    unsigned char reserved_70[0x88 - 0x70];
    int index;                               // +0x88
    int dirty;                               // +0x8C
    FamiliarCallback_00426f70 callback;      // +0x90
    unsigned char reserved_94[0x98 - 0x94];
};

typedef char FamiliarRecordSize[
    sizeof(FamiliarRecord_00426f70) == 0x98 ? 1 : -1];

// The registered animation objects behind the handles.  Bucket nodes alias
// the object's script-id word; children propagate marks when unflagged.
struct FamiliarAnimObject_00426f70;          // the registered Entity

struct FamiliarAnimEntry_00426f70 {
    FamiliarAnimObject_00426f70* object;     // +0x00 registered object
    FamiliarAnimEntry_00426f70* next;        // +0x04 bucket list link
};

struct FamiliarAnimObject_00426f70 {
    int animation_handle;                    // +0x000
    unsigned char reserved_004[0x14 - 0x04];
    FamiliarAnimEntry_00426f70* children;    // +0x014 child node list
    int children_flagged;                    // +0x018 children already marked
    unsigned char reserved_01c[0x304 - 0x01C];
    unsigned short stop_frame;               // +0x304 stop state word
    unsigned char reserved_306[0x35C - 0x306];
    unsigned int flags;                      // +0x35C removal/flag bits
};

struct FamiliarAnimManager_00426f70 {
    unsigned char reserved_000000[0x72DAD4];
    FamiliarAnimEntry_00426f70* primary_head;    // +0x72DAD4
    unsigned char reserved_dad8[4];
    FamiliarAnimEntry_00426f70* secondary_head;  // +0x72DADC
};

// The shot schedule table the player runtime points at (+0x45C): 12-byte
// rows; row k's unfocused offset lives at +0x20 and its focused offset ten
// rows later (+0x98).  Volatile preserves the retail x87 operand order
// (fld [row], fmul [scaler]) under the whole-program pass.
struct FamiliarOffsetRow_00426f70 {
    volatile float x, y, z;
};

struct FamiliarOffsetTable_00426f70 {
    unsigned char reserved_00[0x20];
    union {
        FamiliarOffsetRow_00426f70 carried[26];  // +0x20
        struct {
            FamiliarOffsetRow_00426f70 overlay_pad[10];
            FamiliarOffsetRow_00426f70 focused[26];  // +0x98
        };
    };
};

struct PlayerFamiliarRuntime_00426f70 {
    unsigned char reserved_0000[0x10];
    AnimationResource_00449870* resource;        // +0x010
    unsigned char reserved_0014[0x3CC - 0x14];
    FamiliarPoint_00426f70 anchor;               // +0x3CC
    unsigned char reserved_03d4[0x45C - 0x3D4];
    const FamiliarOffsetTable_00426f70* offsets; // +0x45C
    unsigned char reserved_0460[0x32A0 - 0x460];
    FamiliarRecord_00426f70 familiars[4];        // +0x32A0
    int familiar_count;                          // +0x3500: applied count
    unsigned char reserved_3504[0x436C - 0x3504];
    FamiliarPoint_00426f70 history[33];          // +0x436C
    int alternate;                               // +0x4474
};

// The running game's counters at 0x00474C44 (one object whose address is
// taken elsewhere, so stores through pointers make the compiler reload it).
struct FamiliarGameCounters_00426f70 {
    int score;                                   // 0x00474C44
    short power;                                 // 0x00474C48
    unsigned char reserved_06[0x24 - 0x06];
    int character;                               // 0x00474C68
    int shot_type;                               // 0x00474C6C
};

extern "C" FamiliarGameCounters_00426f70 g_globals_score;
