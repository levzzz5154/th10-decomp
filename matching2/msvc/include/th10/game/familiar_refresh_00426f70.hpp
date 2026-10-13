#pragma once
#include <stddef.h>
#include "th10/game/player_hud_animations.hpp"
#include "th10/render/animation_stop_frame_handle.hpp"

// View of the player runtime used by the familiar refresh at 0x00426F70.
//
// The four familiar/orbit records are interleaved at a 0x98 stride starting
// at player +0x324C.  Each 0x98 slot carries the unfocused and focused offset
// pairs generated for the orbit that ends at this slot (+0x00..+0x0C: the
// next orbit's spawn reference), this orbit's activity state (+0x54), and its
// anchored position (+0x88..+0x94).  The registration side of each orbit
// (animation handle, attached-effect handle, orbit index, dirty flag, update
// callback) sits 0xBC bytes into the same stride.
struct FamiliarOrbitSlot_00426f70 {
    int carried_x;                           // +0x00: unfocused offset x
    int carried_y;                           // +0x04: unfocused offset y
    int focused_x;                           // +0x08: focused offset x
    int focused_y;                           // +0x0C: focused offset y
    unsigned char reserved_10[0x30 - 0x10];
    int stored_count;                        // +0x30: last applied count
    unsigned char reserved_34[0x54 - 0x34];
    int state;                               // +0x54: 0 idle, 2 active
    unsigned char reserved_58[0x88 - 0x58];
    int x;                                   // +0x88
    int y;                                   // +0x8C
    int position_x;                          // +0x90
    int position_y;                          // +0x94
};

typedef char FamiliarOrbitSlotSize[
    sizeof(FamiliarOrbitSlot_00426f70) == 0x98 ? 1 : -1];

typedef int (__fastcall* FamiliarOrbitCallback_00426f70)(void* state);

struct FamiliarOrbitControl_00426f70 {
    int handle;                              // +0x00 (player +0x3308)
    int effect_handle;                       // +0x04 (player +0x330C)
    unsigned char reserved_08[0x20 - 0x08];
    int orbit_index;                         // +0x20 (player +0x3328)
    int dirty;                               // +0x24 (player +0x332C)
    FamiliarOrbitCallback_00426f70 update_callback; // +0x28 (player +0x3330)
    unsigned char reserved_2c[0x98 - 0x2C];
};

typedef char FamiliarOrbitControlSize[
    sizeof(FamiliarOrbitControl_00426f70) == 0x98 ? 1 : -1];

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

// The shot schedule table the player runtime points at (+0x45C).  Row k's
// carried pair lives at +0x20 and its focused pair at +0x98 (the same
// schedule data viewed 0x78 bytes in).  Volatile preserves the retail x87
// operand order (fld [row], fmul [scaler]) under the whole-program pass.
struct FamiliarOffsetTable_00426f70 {
    unsigned char reserved_00[0x20];
    union {
        volatile float carried[26 * 3];          // +0x20, row k at [j]
        struct {
            unsigned char overlay_pad[0x78];
            volatile float second[26 * 3];       // +0x98, row k at [j]
        };
    };
};

struct FamiliarHistoryPoint_00426f70 {
    int x, y;
};

struct PlayerFamiliarRuntime_00426f70 {
    unsigned char reserved_0000[0x10];
    AnimationResource_00449870* resource;        // +0x010
    unsigned char reserved_0014[0x3CC - 0x14];
    int anchor_x;                                // +0x3CC
    int anchor_y;                                // +0x3D0
    unsigned char reserved_03d4[0x45C - 0x3D4];
    const FamiliarOffsetTable_00426f70* offsets; // +0x45C
    unsigned char reserved_0460[0x324C - 0x460];
    FamiliarOrbitSlot_00426f70 orbit_slots[5];   // +0x324C, stride 0x98
    unsigned char reserved_3544[0x436C - 0x3544];
    FamiliarHistoryPoint_00426f70 history[33];   // +0x436C
    int alternate;                               // +0x4474
};
