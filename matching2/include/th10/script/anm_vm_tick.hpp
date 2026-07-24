// =============================================================================
// anm_vm_tick.hpp - ANM script VM per-frame execution surfaces
// Retail functions: 0x0043EE30 (tick), 0x0043EAC0 (special value read)
// =============================================================================
#ifndef TH10_SCRIPT_ANM_VM_TICK_HPP
#define TH10_SCRIPT_ANM_VM_TICK_HPP

#include "th10/math/interpolators.hpp"

// Instruction header layout inside compiled ANM scripts.
struct AnmInstructionView {
    unsigned short opcode;   // +0
    unsigned short size;     // +2 (bytes, includes header)
    short time;              // +4
    unsigned char arg_mask;  // +6 (bit N => argument N is a variable ref)
    const unsigned char* args; // +8
};

// VM flag bits (vm+0x35C) referenced by the tick.
enum AnmVmFlags : unsigned int {
    ANM_FLAG_INTERRUPTED = 0x1,
    ANM_FLAG_DIRTY_SCALE = 0x4,
    ANM_FLAG_DIRTY_GROWTH = 0x8,
    ANM_FLAG_ANCHOR_ALT_POS = 0x100,
    ANM_FLAG_WAITING = 0x1000,
    ANM_FLAG_SCROLL = 0x2000,
    ANM_FLAG_PAUSED = 0x20000,
    ANM_FLAG_RING_MODE_MASK = 0x3C00000,
    ANM_FLAG_RING_MODE = 0x2400000,
    ANM_FLAG_SPEED_OVERRIDE = 0x20000000,
    ANM_FLAG_ALT_RNG = 0x40000000,
};

struct AnmVmState {
    const unsigned char* script_base; // vm+0x38C
    const unsigned char* pc;          // vm+0x390 (0 => script finished)
    int time;                         // vm+0x60 (integer frame clock)
    float time_accumulator;           // vm+0x64
    int previous_time;                // vm+0x5C
    int pending_interrupt;            // vm+0x304
    unsigned int flags;               // vm+0x35C
    float position[3];                // vm+0x334 (or +0x34C when anchored)
    float alt_position[3];            // vm+0x34C
    float velocity[3];                // vm+0x340
    float scale[3];                   // vm+0x24/28/2C
    float scale_velocity[3];          // vm+0x30/34/38
    float growth[2];                  // vm+0x3C/40
    float growth_velocity[2];         // vm+0x44/48
    float rotation[3];                // vm+0x54/58 + z
    float rotation_speed_z;           // vm+0x234
    float rotation_speed_w;           // vm+0x238
    unsigned char color[4];           // vm+0x2FC..2FF (b,g,r,a)
    unsigned char color2[4];          // vm+0x300..303
    int sprite;                       // vm+0x308
    int layer;                        // vm+0x20
    // Saved registers for interrupt return (vm+0x368..+0x37C).
    int saved_time;
    float saved_accumulator;
    int saved_previous_time;
    const unsigned char* saved_pc;
    // Embedded interpolators.
    Interp3F position_interp;         // vm+0xB4 block
    Interp3F scale_interp;            // vm+0x178 block
    Interp2F growth_interp;           // vm+0x1B4 block
    Interp3I color_interp;            // vm+0x100 block
    Interp1I alpha_interp;            // vm+0x12C block
    Interp3I color2_interp;           // vm+0x200 block
    Interp1I alpha2_interp;           // vm+0x22C block
    float speed;                      // *DAT_00476F78 sample
};

struct AnmVmHooks {
    void* context;
    // Variable access (retail 0x0043EC70 / 0x0043EDA0 / 0x0043ED00).
    int (*read_int_arg)(void* context, AnmVmState* vm, const void* slot,
                        int is_variable);
    float (*read_float_arg)(void* context, AnmVmState* vm, const void* slot,
                            int is_variable); // routes through 0x0043EAC0
    int* (*int_var_slot)(void* context, AnmVmState* vm, int id);
    float* (*float_var_slot)(void* context, AnmVmState* vm, int id);
    // Host operations.
    void (*set_sprite)(void* context, AnmVmState* vm, int sprite);
    void (*set_time)(void* context, AnmVmState* vm, float value);
    float (*rand_float)(void* context, int alt_rng);        // 0x0044BB20/BB90
    unsigned int (*rand_u32)(void* context, int alt_rng);   // 0x0043CB80
    float (*wrap_angle)(void* context, float value);        // 0x0044BC10
    void (*start_ring_mode)(void* context, AnmVmState* vm); // 0x004452F0
    void (*spawn_child)(void* context, AnmVmState* vm, int variant,
                        int index);                          // 0x00448D00..
    void (*update_ring_vertices)(void* context, AnmVmState* vm);
    void (*set_blend_bits)(void* context, AnmVmState* vm, unsigned int mask,
                           unsigned int value);
    const float* scroll_delta; // DAT_00491E6C/70/74
};

// Returns 1 when the script ended this frame, 0 when the VM keeps running
// (matching the retail contract where callers test the completion bit).
int AnmVm_Tick(AnmVmState* vm, const AnmVmHooks* hooks);

// Special variable ids accepted by AnmVm_ReadSpecialValue.
enum AnmSpecialVar {
    ANM_VAR_FLOAT_BASE = 10000,   // 0x2710..0x2719 => vm float slots
    ANM_VAR_RAND_ANGLE = 0x271A,  // rand * 2*pi
    ANM_VAR_RAND_SIGNED = 0x271B,
    ANM_VAR_RAND_UNIT = 0x271C,
    ANM_VAR_POS_X = 0x271D,
    ANM_VAR_POS_Y = 0x271E,
    ANM_VAR_POS_Z = 0x271F,
    ANM_VAR_CAMERA_BASE = 0x2720, // 0x2720..0x2725 => global camera values
};

struct AnmSpecialValueHooks {
    void* context;
    float (*rand_unit)(void* context, int alt_rng);   // 0x0044BB90
    float (*rand_signed)(void* context);               // 0x0044BB20
    const float* vm_float_slots;                       // vm+0x30C..
    const float* vm_position;                          // vm+0x334..
    const float* camera_globals;                       // DAT_00491D7C block
    int alt_rng;                                       // flags & 0x40000000
};

float AnmVm_ReadSpecialValue(int id, float fallback,
                             const AnmSpecialValueHooks* hooks);

#endif // TH10_SCRIPT_ANM_VM_TICK_HPP
