#pragma once
#include <stddef.h>
#include "th10/game/right_aligned_text_context/recovery_script_executor_0040bd80.hpp"
#include "th10/game/right_aligned_text_context/entity_movement_slot_0041ab70.hpp"

struct HintPosition_00419120 {
    float x;
    float y;
    float z;
};
// Retail: position EDI; resource, result home, and script on the stack;
// result-home pointer EAX; RET 12. The genuine body is co-visible.
__declspec(noinline) void** __stdcall RecoveryPlayerAnimationCreate_00448db0(
    void* resource, void** result, int script,
    const HintPosition_00419120* position);

struct HintVm_00419120;
struct HintVmLink_00419120 {
    HintVm_00419120* object;
    HintVmLink_00419120* next;
};
struct HintVm_00419120 {
    unsigned int id;
    unsigned char reserved_004[0x10];
    HintVmLink_00419120* children;
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
    HintPosition_00419120 position; // +340
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

struct HintEntry_00419120;
struct HintLink_00419120 {
    HintEntry_00419120* object;
    HintLink_00419120* next;
    HintLink_00419120* previous;
    // Retail receiver EAX; state and release flag on the stack; EAX=0; RET 8.
    __declspec(noinline) int Drain(
        struct HintUpdateView* state, int release);
};
struct HintEntry_00419120 {
    HintPosition_00419120 position;
    unsigned int reserved_00c;
    HintLink_00419120* next;     // +010
    HintLink_00419120* previous; // +014
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
struct HintUpdateView {
    unsigned char reserved_000[0xDC];
    unsigned int handles[10];               // +0DC
    HintPosition_00419120 positions[10]; // +104
    float values[10];                       // +17C
    int slot;                              // +1A4
};

typedef char HintEntryPositionCheck[(offsetof(HintEntry_00419120,position)==0)?1:-1];
typedef char HintEntryTextCheck[(offsetof(HintEntry_00419120,text)==0x1C)?1:-1];
typedef char HintEntryCountdownCheck[(offsetof(HintEntry_00419120,countdown)==0x60)?1:-1];
typedef char HintEntryIntensityCheck[(offsetof(HintEntry_00419120,intensity)==0x7C)?1:-1];
typedef char HintEntryColorCheck[(offsetof(HintEntry_00419120,color)==0x84)?1:-1];
typedef char HintEntrySizeCheck[(sizeof(HintEntry_00419120)==0x88)?1:-1];
typedef char HintStateHandlesCheck[(offsetof(HintUpdateView,handles)==0xDC)?1:-1];
typedef char HintStatePositionCheck[(offsetof(HintUpdateView,positions)==0x104)?1:-1];
typedef char HintStateValuesCheck[(offsetof(HintUpdateView,values)==0x17C)?1:-1];
typedef char HintStateSlotCheck[(offsetof(HintUpdateView,slot)==0x1A4)?1:-1];
typedef char HintStateSizeCheck[(sizeof(HintUpdateView)==0x1A8)?1:-1];
typedef char HintVmChildrenCheck[(offsetof(HintVm_00419120,children)==0x14)?1:-1];
typedef char HintVmColorCheck[(offsetof(HintVm_00419120,color)==0x2FC)?1:-1];
typedef char HintVmTimestampCheck[(offsetof(HintVm_00419120,timestamp)==0x30C)?1:-1];
typedef char HintVmPositionCheck[(offsetof(HintVm_00419120,position)==0x340)?1:-1];
typedef char HintVmFlagsCheck[(offsetof(HintVm_00419120,flags)==0x35C)?1:-1];
typedef char HintVmFontCheck[(offsetof(HintVm_00419120,font_height)==0x3A0)?1:-1];
typedef char HintVmWidthCheck[(offsetof(HintVm_00419120,font_width)==0x3A1)?1:-1];
