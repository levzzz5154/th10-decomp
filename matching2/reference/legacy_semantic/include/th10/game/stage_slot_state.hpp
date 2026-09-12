// =============================================================================
// stage_slot_state.hpp - Per-stage slot state construction
// Retail function: 0x00415B00
// =============================================================================
#ifndef TH10_GAME_STAGE_SLOT_STATE_HPP
#define TH10_GAME_STAGE_SLOT_STATE_HPP

#include "th10/math/timer.hpp"

enum {
    // Dword index of the animation archive inside the resource object.
    STAGE_SLOT_ARCHIVE_INDEX = 8807,
    // Script slot passed to the two sparkle VMs.
    STAGE_SLOT_VM_SCRIPT = 15,
    // Flag forced into the VM control word at dword 215.
    STAGE_SLOT_VM_FLAG = 0x40000000,
    // Byte written to the two resolved record fields.
    STAGE_SLOT_RECORD_VALUE = 16,
    STAGE_SLOT_RECORD_FIELD_A = 928,
    STAGE_SLOT_RECORD_FIELD_B = 929
};

// The 0x90-byte slot allocated by the caller at 0x00415DB0.
struct StageSlotState {
    int id;                        // +0x00, filled in by the caller
    FrameTimer timer_a;            // +0x04
    FrameTimer timer_b;            // +0x18
    FrameTimer timer_c;            // +0x2C
    unsigned int reserved_40[3];   // +0x40
    int vm_handle_a;               // +0x4C
    int vm_handle_b;               // +0x50
    unsigned int reserved_54;      // +0x54
    unsigned int field_58;         // +0x58
    const void* definition;        // +0x5C
    float radius;                  // +0x60, 8.0f
    unsigned int reserved_64[2];   // +0x64
    float region[3];               // +0x6C, 25.0f and two zeros
    unsigned int reserved_78[2];   // +0x78
    unsigned int field_80;         // +0x80
    unsigned int field_84;         // +0x84
    unsigned int color_a;          // +0x88, 0x00F8F08F
    unsigned int color_b;          // +0x8C, 0x008088FF
};

// Singly linked effect node walked during teardown.
struct StageEffectNode {
    void* vtable;           // +0x00
    unsigned int reserved_04;
    StageEffectNode* next;  // +0x08
    int kind;               // +0x0C
};

struct StageSlotInitHooks {
    void* context;
    // Retail 0x004776F0: carries the 2000-entry pool at +0x60.
    unsigned char* pool_object;
    // Retail 0x004776E0: carries the animation archive at dword 8807.
    void* const* resource_object;
    // Retail 0x00491C10.
    void* game_state;
    // Retail 0x00449950, 0x00449870, 0x004489D0, 0x004491C0.
    unsigned int* (*allocate_vm)(void* game_state);
    void (*init_script)(void* archive, unsigned int* vm, int index);
    int (*register_vm)(void* game_state, unsigned int* vm);
    unsigned char* (*find_vm)(void* game_state, int handle);
    // Retail 0x00408030, typed elsewhere as ScoreState_ActivateFromResult.
    // The retail call passes the region pointer and the entry in registers;
    // the argument order there is not reliably attributable, so the edge is
    // kept as a hook rather than asserting a binding.
    void (*activate_entry)(void* context, float* region, unsigned char* entry);
    // Head of the teardown list, retail *(0x0047781C + 0x18).
    StageEffectNode* effect_list;
    // Vtable slot 5 invoked with a zero argument.
    void (*release_effect)(StageEffectNode* node);
    // Retail 0x0040E6A0 applied to the message host at 0x00477704.
    void (*flush_message_host)(void* context);
};

// Returns the slot, matching retail.
StageSlotState* StageSlotState_Init(StageSlotState* slot,
                                    const void* definition,
                                    const StageSlotInitHooks* hooks);

#endif // TH10_GAME_STAGE_SLOT_STATE_HPP
