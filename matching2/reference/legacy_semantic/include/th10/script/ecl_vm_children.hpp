#pragma once

// ECL child VM spawn and per-frame tick (retail 0x004500D0, 0x0044FD10).
#include "th10/util/scalars.hpp"

struct EclChildLink {
    void* vm;                     // retail +0x00: owned child VM
    EclChildLink* next;     // retail +0x04
    EclChildLink* previous; // retail +0x08
};

// Conventional view of the interpreter fields the child-list leaves touch.
struct EclOwner {
    void* active_vm;              // retail +0x0004: VM the interpreter runs next
    void* root_vm;                // retail +0x0008: embedded top-level VM
    EclChildLink anchor;    // retail +0x1030: list anchor; anchor.next is the head
};

// ABI-compatible child VM record (0x1024 retail bytes).
struct EclChildVm {
    Word instruction_offset;      // retail +0x0000, cleared
    Word wait_counter;            // retail +0x0004, cleared
    Byte script_state[0x1000];    // retail +0x0008..+0x1007
    Word interpolator_slot_a;     // retail +0x1008, cleared
    Word interpolator_slot_b;     // retail +0x100C, cleared
    void* script;                       // retail +0x1010
    void* owner;                        // retail +0x1014
    Word reserved_1018;           // retail +0x1018
    Byte difficulty_mask;         // retail +0x101C, copied from the active VM
    Byte padding[7];              // fill to 0x1024
};

EclChildVm* EclVm_SpawnChild(EclOwner* owner, void* script,
                                   float* start_argument,
                                   void* (*allocate)(unsigned int size),
                                   void (*start)(void* active_vm,
                                                 float* argument));

int EclVm_TickChildren(EclOwner* owner, float frame_delta,
                       int (*tick)(EclOwner* owner, float delta),
                       void (*free_memory)(void* memory));

union EclStartValue {
    int int_value;
    float float_value;
};

struct EclStartArgument {
    char source_type;
    char destination_type;
    EclStartValue value;
};

struct EclStartInstruction {
    const unsigned short* label;
    const EclStartArgument* arguments;
    unsigned int argument_count;
};

struct EclStartVm {
    unsigned int instruction_offset;
    void* instruction;
    Byte stack[0x1000];
    unsigned int stack_top;
};

struct EclStartOwner {
    EclStartVm* active_vm;
};

struct EclStartHooks {
    float (*resolve_float)(EclStartVm* parent, unsigned int argument_index,
                           float encoded);
    int (*resolve_int)(EclStartVm* parent, unsigned int argument_index,
                       int encoded);
    void* (*find_label)(const unsigned short* label);
};

// 0x0044DF70 - Marshal an ECL call's remaining arguments into a child VM,
// install its entry label, and preserve/restore the owner's active VM.
int EclVm_StartChild(EclStartVm* child, EclStartVm* parent,
                     EclStartOwner* owner,
                     const EclStartInstruction* instruction,
                     unsigned int first_argument,
                     const EclStartHooks* hooks);
