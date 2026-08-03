#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

#include "th10/math/timer.hpp"

// One 0x6C-byte indicator slot in the effect manager's 0x20-entry pool
// at retail manager+0x350C. Retail word offsets in comments; the host
// layout grows where the embedded timer stores a pointer.
struct EffectIndicatorSlot {
    uint32_t kind;              // word 0x00
    uint32_t argument;          // word 0x01
    uint32_t reserved_08[4];    // words 0x02..0x05
    float x;                    // word 0x06
    float y;                    // word 0x07
    float z;                    // word 0x08
    uint32_t reserved_24[8];    // words 0x09..0x10
    EmbeddedTimerState timer;   // words 0x11..0x15
    uint32_t mode;              // word 0x16
    uint32_t counter;           // word 0x17, cleared on allocate
    int32_t limit;              // word 0x18, 999999 on allocate
    int32_t phase;              // word 0x19, 4 on allocate
    uint32_t flags;             // word 0x1A, bit 0 in-use, bit 1 active
};

// Effect manager fragment: the slot pool lives at retail +0x350C.
struct EffectIndicatorPool {
    EffectIndicatorSlot slots[0x20];
};

// 0x00427B50 - Allocate the first free indicator slot: wipe it, mark it
// in-use and active, store the position / kind / argument, arm the
// embedded countdown timer with the given frame count, and apply the
// mode and {counter 0, limit 999999, phase 4} defaults. When every slot
// is taken, retail returns the address one past the pool; the readable
// form mirrors that with the one-past-the-end slot pointer.
EffectIndicatorSlot* EffectIndicatorPool_Allocate(EffectIndicatorPool* pool,
                                                  const float position[3],
                                                  uint32_t kind,
                                                  uint32_t argument,
                                                  int32_t frames,
                                                  uint32_t mode);

// 0x0042A930 - Arm an embedded countdown timer: run the shared
// first-use sentinel initialization when needed, then set current to
// the frame count, target to frames - 1, and store the frame count's
// float image in the previous slot. Retail receives the owning object
// in EAX with the timer at +0x14.
void EmbeddedTimer_SetCountdown(EmbeddedTimerState* timer, int32_t frames);

// 0x00427D80 - Multiply an integer pair into an output pair. Retail
// carries the output in EAX (fastcall: pair in ECX, scale in EDX).
void CellPair_Scale(int32_t out[2], const int32_t pair[2], int32_t scale);


// One entry in the 0x80-entry watch/effect pool at retail player+0x49C.
// This is a readable host layout; retail uses a 0x5C-byte packed record.
struct EffectWatchSlot;
struct EffectWatchManager;

struct EffectWatchDescriptor {
    int8_t period;              // +0x00, consumed by caller 0x00428160
    int8_t phase;               // +0x01, consumed by caller 0x00428160
    uint8_t reserved_02[2];
    float offset_x;             // +0x04
    float offset_y;             // +0x08
    uint8_t reserved_0c[8];
    float angle;                // +0x14
    float radius;               // +0x18
    int8_t source_index;        // +0x1C
    uint8_t mode;               // +0x1D; 3 enables exclusivity/secondary VM
    int16_t script_index;       // +0x1E; primary script is this + 5
    uint8_t reserved_20[2];
    int16_t sound_id;           // +0x22; negative disables sound
    void (*callback)(EffectWatchManager*, EffectWatchSlot*, int); // +0x24
};

struct EffectWatchSourcePosition {
    int32_t x_hundredths;
    int32_t y_hundredths;
};

struct EffectWatchSlot {
    EmbeddedTimerState timer;
    float origin[3];
    float polar[3];
    float radius;
    float angle;
    float phase;
    float phase_delta;
    uint32_t flags;             // persistent across reuse; bit 0 selects carry path
    int32_t active;
    int32_t primary_handle;
    int32_t secondary_handle;
    const EffectWatchDescriptor* descriptor;
};

struct EffectWatchManager {
    EffectWatchSlot slots[0x80];
    float player_position[3];
    EffectWatchSourcePosition sources[0x80];
    uint8_t exclusive_active[0x80];
    void* animation_owner;
};

struct EffectWatchEnvironment {
    void* context;
    float (*normalize_angle)(float angle);
    void (*set_polar)(float out[3], float angle, float radius);
    void* (*allocate_vm)(void* context);
    void (*prepare_vm)(void* context, void* vm, int layer,
                       uint32_t flags_or, void* animation_owner, int script);
    int32_t (*register_vm)(void* context, void* vm);
    void* (*find_vm)(void* context, int32_t handle);
    uint32_t (*get_vm_flags)(void* context, void* vm);
    void (*set_vm_angle_and_flags)(void* context, void* vm, float angle,
                                   uint32_t flags_or);
    void (*queue_sound)(void* context, int16_t sound_id, float stamp);
};

// 0x00427E90 - Allocate and initialize one watch/effect record from a
// 0x34-byte descriptor, create its animation VM(s), run the optional callback,
// and queue the optional sound. Returns zero like retail; a full pool and an
// already-active mode-3 source are silent no-ops.
int EffectWatch_SpawnFromDescriptor(EffectWatchManager* manager,
                                    const EffectWatchDescriptor* descriptor,
                                    int callback_argument,
                                    const EffectWatchEnvironment* environment);
