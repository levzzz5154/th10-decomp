#pragma once
#include <stddef.h>
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_0040bd80.hpp"
#include "th10/game/marktext_dispatcher_context/entity_movement_slot_0041ab70.hpp"

struct RecoveryIndicatorPosition_00419120 {
    float x;
    float y;
    float z;
};
// 0x00448DB0: starts script `script` of a loaded animation file as a new VM at
// a playfield position, writes its handle to `result` and returns `result`.
// Retail: position EDI; resource, result home, and script on the stack;
// result-home pointer EAX; RET 12. The genuine body is co-visible.
__declspec(noinline) void** __stdcall RecoveryPlayerAnimationCreate_00448db0(
    void* resource, void** result, int script,
    const RecoveryIndicatorPosition_00419120* position);

struct RecoveryIndicatorVm_00419120;
struct RecoveryIndicatorVmLink_00419120 {
    RecoveryIndicatorVm_00419120* object;
    RecoveryIndicatorVmLink_00419120* next;
};
struct RecoveryIndicatorVm_00419120 {
    unsigned int id;
    unsigned char reserved_004[0x10];
    RecoveryIndicatorVmLink_00419120* children;
    int children_flagged;
    unsigned char reserved_01c[0x24];
    float scale_y;                          // +040
    unsigned char reserved_044[0x0C];
    float height;                           // +050
    unsigned char reserved_054[0xD8];
    int interrupt_pending;                  // +12C
    unsigned char reserved_130[0x1CC];
    union {
        unsigned int word;
        unsigned char bytes[4];
    } color;                                // +2FC
    unsigned char reserved_300[0x0C];
    unsigned int timestamp;                 // +30C
    // Alpha the text fades back to once the player moves away. Stored as a
    // whole word; only its low byte is ever nonzero.
    union {
        int opacity;
        unsigned char opacity_byte;
    };                                      // +310
    unsigned char reserved_314[0x2C];
    RecoveryIndicatorPosition_00419120 position; // +340
    unsigned char reserved_34c[0x10];
    unsigned int flags;                     // +35C
    unsigned int mode_flags;                // +360
    unsigned char reserved_364[0x30];
    RecoveryTextResource_004479d0* resource; // +394
    unsigned char reserved_398[8];
    unsigned char font_height;              // +3A0
    unsigned char font_width;               // +3A1

    __declspec(noinline) void __cdecl FormatCentered(
        void* manager, ...);
    __declspec(noinline) void __cdecl FormatRightAligned(
        void* manager, ...);
};

struct RecoveryIndicatorEntry_00419120;
struct RecoveryIndicatorLink_00419120 {
    RecoveryIndicatorEntry_00419120* object;
    RecoveryIndicatorLink_00419120* next;
    RecoveryIndicatorLink_00419120* previous;
    // Retail receiver EAX; state and release flag on the stack; EAX=0; RET 8.
    __declspec(noinline) int Drain(
        struct RecoveryIndicatorState_00419120* state, int release);
};
struct RecoveryIndicatorEntry_00419120 {
    RecoveryIndicatorPosition_00419120 position;
    unsigned int reserved_00c;
    RecoveryIndicatorLink_00419120* next;     // +010
    RecoveryIndicatorLink_00419120* previous; // +014
    unsigned int reserved_018;
    char text[0x44];
    int countdown;                          // +060
    int anchor_mode;                        // +064
    int owner_tag;                          // +068
    unsigned int timestamp;                 // +06C
    unsigned char reserved_070[0x0C];
    float intensity;                        // +07C
    float offset;                           // +080
    union {
        unsigned int word;
        unsigned char bytes[4];
    } color;                                // +084
};
// Handle of one animation VM: the VM's id, or zero for none.
struct RecoveryIndicatorHandle_00419120 {
    unsigned int value;
};
// One of the sixteen pending-text queues, selected by the current stage.
struct RecoveryIndicatorQueue_00419120 {
    void* owner;
    RecoveryIndicatorLink_00419120* head;
    RecoveryIndicatorLink_00419120* tail;
};
// The floating text manager: queued texts and the ten on-screen text sprites.
struct RecoveryIndicatorState_00419120 {
    unsigned int flags;
    unsigned int reserved_004;
    void* update_task;                      // +008
    void* draw_task;                        // +00C
    int frame;                              // +010
    int stage_frame;                        // +014, restarts when the stage changes
    RecoveryIndicatorQueue_00419120 queues[16]; // +018
    int owner_tag;                          // +0D8
    RecoveryIndicatorHandle_00419120 handles[10]; // +0DC
    RecoveryIndicatorPosition_00419120 positions[10]; // +104
    float widths[10];                       // +17C
    int slot;                              // +1A4, next sprite slot to reuse

    // Retail receiver EBX; EAX=1; plain RET.
    __declspec(noinline) int Update();
};

typedef char RecoveryIndicatorEntryPositionCheck[(offsetof(RecoveryIndicatorEntry_00419120,position)==0)?1:-1];
typedef char RecoveryIndicatorEntryTextCheck[(offsetof(RecoveryIndicatorEntry_00419120,text)==0x1C)?1:-1];
typedef char RecoveryIndicatorEntryCountdownCheck[(offsetof(RecoveryIndicatorEntry_00419120,countdown)==0x60)?1:-1];
typedef char RecoveryIndicatorEntryIntensityCheck[(offsetof(RecoveryIndicatorEntry_00419120,intensity)==0x7C)?1:-1];
typedef char RecoveryIndicatorEntryColorCheck[(offsetof(RecoveryIndicatorEntry_00419120,color)==0x84)?1:-1];
typedef char RecoveryIndicatorEntrySizeCheck[(sizeof(RecoveryIndicatorEntry_00419120)==0x88)?1:-1];
typedef char RecoveryIndicatorStateHandlesCheck[(offsetof(RecoveryIndicatorState_00419120,handles)==0xDC)?1:-1];
typedef char RecoveryIndicatorStatePositionCheck[(offsetof(RecoveryIndicatorState_00419120,positions)==0x104)?1:-1];
typedef char RecoveryIndicatorStateValuesCheck[(offsetof(RecoveryIndicatorState_00419120,widths)==0x17C)?1:-1];
typedef char RecoveryIndicatorStateQueuesCheck[(offsetof(RecoveryIndicatorState_00419120,queues)==0x18)?1:-1];
typedef char RecoveryIndicatorStateOwnerCheck[(offsetof(RecoveryIndicatorState_00419120,owner_tag)==0xD8)?1:-1];
typedef char RecoveryIndicatorStateSlotCheck[(offsetof(RecoveryIndicatorState_00419120,slot)==0x1A4)?1:-1];
typedef char RecoveryIndicatorStateSizeCheck[(sizeof(RecoveryIndicatorState_00419120)==0x1A8)?1:-1];
typedef char RecoveryIndicatorVmChildrenCheck[(offsetof(RecoveryIndicatorVm_00419120,children)==0x14)?1:-1];
typedef char RecoveryIndicatorVmScaleCheck[(offsetof(RecoveryIndicatorVm_00419120,scale_y)==0x40)?1:-1];
typedef char RecoveryIndicatorVmHeightCheck[(offsetof(RecoveryIndicatorVm_00419120,height)==0x50)?1:-1];
typedef char RecoveryIndicatorVmInterruptCheck[(offsetof(RecoveryIndicatorVm_00419120,interrupt_pending)==0x12C)?1:-1];
typedef char RecoveryIndicatorVmOpacityCheck[(offsetof(RecoveryIndicatorVm_00419120,opacity)==0x310)?1:-1];
typedef char RecoveryIndicatorVmColorCheck[(offsetof(RecoveryIndicatorVm_00419120,color)==0x2FC)?1:-1];
typedef char RecoveryIndicatorVmTimestampCheck[(offsetof(RecoveryIndicatorVm_00419120,timestamp)==0x30C)?1:-1];
typedef char RecoveryIndicatorVmPositionCheck[(offsetof(RecoveryIndicatorVm_00419120,position)==0x340)?1:-1];
typedef char RecoveryIndicatorVmFlagsCheck[(offsetof(RecoveryIndicatorVm_00419120,flags)==0x35C)?1:-1];
typedef char RecoveryIndicatorVmFontCheck[(offsetof(RecoveryIndicatorVm_00419120,font_height)==0x3A0)?1:-1];
typedef char RecoveryIndicatorVmWidthCheck[(offsetof(RecoveryIndicatorVm_00419120,font_width)==0x3A1)?1:-1];
