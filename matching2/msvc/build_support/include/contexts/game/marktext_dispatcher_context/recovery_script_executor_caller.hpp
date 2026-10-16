#pragma once
#include <stddef.h>
#include "recovery_script_executor.hpp"
#include "entity_movement_slot.hpp"

struct HintPosition {
    float x;
    float y;
    float z;
};
// 0x00448DB0: starts script `script` of a loaded animation file as a new VM at
// a playfield position, writes its handle to `result` and returns `result`.
// Retail: position EDI; resource, result home, and script on the stack;
// result-home pointer EAX; RET 12. The genuine body is co-visible.
__declspec(noinline) void** __stdcall RecoveryPlayerAnimationCreate(
    void* resource, void** result, int script,
    const HintPosition* position);

struct HintVm;
struct HintVmLink {
    HintVm* object;
    HintVmLink* next;
};
struct HintVm {
    unsigned int id;
    unsigned char reserved_004[0x10];
    HintVmLink* children;
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
    HintPosition position; // +340
    unsigned char reserved_34c[0x10];
    unsigned int flags;                     // +35C
    unsigned int mode_flags;                // +360
    unsigned char reserved_364[0x30];
    RecoveryTextResource* resource; // +394
    unsigned char reserved_398[8];
    unsigned char font_height;              // +3A0
    unsigned char font_width;               // +3A1

    __declspec(noinline) void __cdecl FormatCentered(
        void* manager, ...);
    __declspec(noinline) void __cdecl FormatRightAligned(
        void* manager, ...);
};

struct HintEntry;
struct HintLink {
    HintEntry* object;
    HintLink* next;
    HintLink* previous;
    // Retail receiver EAX; state and release flag on the stack; EAX=0; RET 8.
    __declspec(noinline) int Drain(
        struct HintUpdateView* state, int release);
};
struct HintEntry {
    HintPosition position;
    unsigned int reserved_00c;
    HintLink* next;     // +010
    HintLink* previous; // +014
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
struct HintHandle {
    unsigned int value;
};
// One of the sixteen pending-text queues, selected by the current stage.
struct HintQueue_00419120 {
    void* owner;
    HintLink* head;
    HintLink* tail;
};
// The floating text manager: queued texts and the ten on-screen text sprites.
struct HintUpdateView {
    unsigned int flags;
    unsigned int reserved_004;
    void* update_task;                      // +008
    void* draw_task;                        // +00C
    int frame;                              // +010
    int stage_frame;                        // +014, restarts when the stage changes
    HintQueue_00419120 queues[16]; // +018
    int owner_tag;                          // +0D8
    HintHandle handles[10]; // +0DC
    HintPosition positions[10]; // +104
    float widths[10];                       // +17C
    int slot;                              // +1A4, next sprite slot to reuse

    // Retail receiver EBX; EAX=1; plain RET.
    __declspec(noinline) int Update();
};

typedef char HintEntryPositionCheck[(offsetof(HintEntry,position)==0)?1:-1];
typedef char HintEntryTextCheck[(offsetof(HintEntry,text)==0x1C)?1:-1];
typedef char HintEntryCountdownCheck[(offsetof(HintEntry,countdown)==0x60)?1:-1];
typedef char HintEntryIntensityCheck[(offsetof(HintEntry,intensity)==0x7C)?1:-1];
typedef char HintEntryColorCheck[(offsetof(HintEntry,color)==0x84)?1:-1];
typedef char HintEntrySizeCheck[(sizeof(HintEntry)==0x88)?1:-1];
typedef char HintStateHandlesCheck[(offsetof(HintUpdateView,handles)==0xDC)?1:-1];
typedef char HintStatePositionCheck[(offsetof(HintUpdateView,positions)==0x104)?1:-1];
typedef char HintStateValuesCheck[(offsetof(HintUpdateView,widths)==0x17C)?1:-1];
typedef char HintStateQueuesCheck[(offsetof(HintUpdateView,queues)==0x18)?1:-1];
typedef char HintStateOwnerCheck[(offsetof(HintUpdateView,owner_tag)==0xD8)?1:-1];
typedef char HintStateSlotCheck[(offsetof(HintUpdateView,slot)==0x1A4)?1:-1];
typedef char HintStateSizeCheck[(sizeof(HintUpdateView)==0x1A8)?1:-1];
typedef char HintVmChildrenCheck[(offsetof(HintVm,children)==0x14)?1:-1];
typedef char HintVmScaleCheck[(offsetof(HintVm,scale_y)==0x40)?1:-1];
typedef char HintVmHeightCheck[(offsetof(HintVm,height)==0x50)?1:-1];
typedef char HintVmInterruptCheck[(offsetof(HintVm,interrupt_pending)==0x12C)?1:-1];
typedef char HintVmOpacityCheck[(offsetof(HintVm,opacity)==0x310)?1:-1];
typedef char HintVmColorCheck[(offsetof(HintVm,color)==0x2FC)?1:-1];
typedef char HintVmTimestampCheck[(offsetof(HintVm,timestamp)==0x30C)?1:-1];
typedef char HintVmPositionCheck[(offsetof(HintVm,position)==0x340)?1:-1];
typedef char HintVmFlagsCheck[(offsetof(HintVm,flags)==0x35C)?1:-1];
typedef char HintVmFontCheck[(offsetof(HintVm,font_height)==0x3A0)?1:-1];
typedef char HintVmWidthCheck[(offsetof(HintVm,font_width)==0x3A1)?1:-1];
