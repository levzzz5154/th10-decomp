#pragma once

#include <cstdint>

struct AnmObject;

// Child list node (retail two-word node: object pointer, next pointer).
struct AnmChildNode {
    AnmObject* object;
    AnmChildNode* next;
};

// Animation object fragment (retail offsets in comments).
struct AnmObject {
    AnmChildNode* children;  // +0x14, singly linked child list
    int32_t solo;            // +0x18, non-zero blocks child propagation
    uint16_t sprite_word;    // +0x304, propagated value
};

// Handle resolver edge (retail FUN_004491C0 against the global game
// state manager).
typedef AnmObject* (*AnmResolveFn)(uint32_t handle);

// 0x00409E50 - Resolve the animation handle in the given slot and set
// its sprite word to 1, propagating to every child when the object is
// not solo. Retail carries the handle slot in EAX.
void Anm_MarkHandleAndChildren(const uint32_t* handle_slot,
                               AnmResolveFn resolve);

// 0x0042C770 - Resolve the handle at the given index of the owner's
// handle table (retail owner+0x2C4) and store the sprite word,
// propagating to every child when the object is not solo. Retail passes
// the value in SI.
void Anm_SetSpriteWordForSlot(const uint32_t* handle_table, int32_t index,
                              uint16_t value, AnmResolveFn resolve);
