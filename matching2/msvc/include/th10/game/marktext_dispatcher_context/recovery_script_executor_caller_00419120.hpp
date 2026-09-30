#pragma once
#include <stddef.h>
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_0040bd80.hpp"
#include "th10/game/marktext_dispatcher_context/entity_movement_slot_0041ab70.hpp"

struct RecoveryIndicatorPosition_00419120 {
    float x;
    float y;
    float z;
};
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
    unsigned char reserved_01c[0x2E0];
    union {
        unsigned int word;
        unsigned char bytes[4];
    } color;                                // +2FC
    unsigned char reserved_300[0x0C];
    unsigned int timestamp;                 // +30C
    unsigned int opacity;                   // +310
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
struct RecoveryIndicatorState_00419120 {
    unsigned char reserved_000[0xDC];
    unsigned int handles[10];               // +0DC
    RecoveryIndicatorPosition_00419120 positions[10]; // +104
    float values[10];                       // +17C
    int slot;                              // +1A4
};

typedef char RecoveryIndicatorEntryPositionCheck[(offsetof(RecoveryIndicatorEntry_00419120,position)==0)?1:-1];
typedef char RecoveryIndicatorEntryTextCheck[(offsetof(RecoveryIndicatorEntry_00419120,text)==0x1C)?1:-1];
typedef char RecoveryIndicatorEntryCountdownCheck[(offsetof(RecoveryIndicatorEntry_00419120,countdown)==0x60)?1:-1];
typedef char RecoveryIndicatorEntryIntensityCheck[(offsetof(RecoveryIndicatorEntry_00419120,intensity)==0x7C)?1:-1];
typedef char RecoveryIndicatorEntryColorCheck[(offsetof(RecoveryIndicatorEntry_00419120,color)==0x84)?1:-1];
typedef char RecoveryIndicatorEntrySizeCheck[(sizeof(RecoveryIndicatorEntry_00419120)==0x88)?1:-1];
typedef char RecoveryIndicatorStateHandlesCheck[(offsetof(RecoveryIndicatorState_00419120,handles)==0xDC)?1:-1];
typedef char RecoveryIndicatorStatePositionCheck[(offsetof(RecoveryIndicatorState_00419120,positions)==0x104)?1:-1];
typedef char RecoveryIndicatorStateValuesCheck[(offsetof(RecoveryIndicatorState_00419120,values)==0x17C)?1:-1];
typedef char RecoveryIndicatorStateSlotCheck[(offsetof(RecoveryIndicatorState_00419120,slot)==0x1A4)?1:-1];
typedef char RecoveryIndicatorStateSizeCheck[(sizeof(RecoveryIndicatorState_00419120)==0x1A8)?1:-1];
typedef char RecoveryIndicatorVmChildrenCheck[(offsetof(RecoveryIndicatorVm_00419120,children)==0x14)?1:-1];
typedef char RecoveryIndicatorVmColorCheck[(offsetof(RecoveryIndicatorVm_00419120,color)==0x2FC)?1:-1];
typedef char RecoveryIndicatorVmTimestampCheck[(offsetof(RecoveryIndicatorVm_00419120,timestamp)==0x30C)?1:-1];
typedef char RecoveryIndicatorVmPositionCheck[(offsetof(RecoveryIndicatorVm_00419120,position)==0x340)?1:-1];
typedef char RecoveryIndicatorVmFlagsCheck[(offsetof(RecoveryIndicatorVm_00419120,flags)==0x35C)?1:-1];
typedef char RecoveryIndicatorVmFontCheck[(offsetof(RecoveryIndicatorVm_00419120,font_height)==0x3A0)?1:-1];
typedef char RecoveryIndicatorVmWidthCheck[(offsetof(RecoveryIndicatorVm_00419120,font_width)==0x3A1)?1:-1];
