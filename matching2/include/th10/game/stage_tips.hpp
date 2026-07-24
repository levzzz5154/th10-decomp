#pragma once

#include "th10/game/entity.hpp"

struct StageTip;

// Three-word intrusive list node shared by the stage-tip manager's
// sentinels and the node embedded in each tip at retail +0x0C. In
// retail each field is one 32-bit slot; the readable form uses native
// pointers and documents the retail offsets.
struct StageTipNode {
    StageTip* owner;        // +0x00, the containing tip (or manager)
    StageTipNode* next;     // +0x04
    StageTipNode* previous; // +0x08
};

// One parsed entry from the stage Tips sections. The parser allocates these
// as 0x88-byte records and links them through the node below.
struct StageTip {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
    StageTipNode node;          // +0x0C {owner=self, next, previous}
    uint8_t reserved_018[4];    // +0x18
    char name[0x40];            // +0x1C, strncpy'd tip text
    uint8_t reserved_05C[4];    // +0x5C
    int32_t display_value;      // +0x60, from DAT_00474C88/DAT_00474C8C
    int32_t display_zero;       // +0x64, cleared on creation
    int32_t display_mode;       // +0x68, copy of DAT_00474C84
    int32_t duration;           // +0x6C, defaults to 300 frames
    int32_t selection;          // +0x70, defaults to -1; 0x1E once linked
    uint8_t reserved_074[0x7C - 0x74];
    float scale;                // +0x7C, defaults to 1.0
    uint32_t rendered_width;    // +0x80
    int32_t state;              // +0x84, defaults to -1
};
// sizeof(StageTip) == 0x88 under the 32-bit production compiler

// Stage-tip manager published through the retail global at 0x00477814.
// Retail size is 0x1A8 bytes: a flags word, five reserved words, the
// sixteen list sentinels at +0x18..+0xD8 (12 bytes each), and reserved
// trailing state. Sentinels 8..15 (retail +0x78 onward) hold the
// per-difficulty stage-tip chains indexed by DAT_00474C7C.
struct StageTipManager {
    uint32_t flags;             // +0x00, bit 1 set by the constructor
    uint32_t reserved_04[5];    // +0x04..+0x14
    StageTipNode lists[16];     // +0x18..+0xD8 (retail 12-byte stride)
    uint32_t reserved_D8[0x34]; // +0xD8..+0x1A8
};

StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip);

// 0x00418D40 - Zero the manager, mark it constructed, self-link the
// sixteen sentinels, and publish it through DAT_00477814.
StageTipManager* StageTipManager_Construct(StageTipManager* state);

// 0x0041A120 - Allocate and initialize one tip record, append it to the
// tail of the current difficulty's chain, and populate its position,
// text, and display fields from the difficulty globals.
StageTip* StageTip_Create(StageTipManager* manager, const float position[3],
                          const char* text, void* (*allocate)(uint32_t));

// Create the short-lived highlighted tip variant after aging the active
// difficulty list by one selection step.
StageTip* StageTip_CreateUrgent(StageTipManager* manager,
                                const float position[3], const char* text,
                                void* (*allocate)(uint32_t));
