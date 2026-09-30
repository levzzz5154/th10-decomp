#pragma once
#include <stddef.h>
#include "th10/game/scheduler.hpp"
#include "th10/math/timer.hpp"

// Full 0x44-byte ASCII overlay state used by 0043C8B0 and 0043C970.
struct RecoveryAsciiManager_0043c8b0 {
    unsigned int flags;                    // +00
    unsigned int reserved_04;
    SchedulerTask* update_task;             // +08
    SchedulerTask* draw_task;               // +0C
    unsigned int mode;                      // +10
    unsigned int reserved_14;
    unsigned int color;                     // +18
    unsigned int payload;                   // +1C
    unsigned int argument_20;
    unsigned int argument_24;
    unsigned int argument_28;
    unsigned int reserved_2c;
    FrameTimer timer;                       // +30

    RecoveryAsciiManager_0043c8b0() { timer.flags &= ~1u; }
};

typedef char RecoveryAscii_size_44[
    sizeof(RecoveryAsciiManager_0043c8b0) == 0x44 ? 1 : -1];
typedef char RecoveryAscii_timer_offset_30[
    offsetof(RecoveryAsciiManager_0043c8b0, timer) == 0x30 ? 1 : -1];
typedef char RecoveryAscii_timer_flags_offset_40[
    offsetof(RecoveryAsciiManager_0043c8b0, timer) +
    offsetof(FrameTimer, flags) == 0x40 ? 1 : -1];

extern "C" {
// Logical draw_priority arrives in EBX in the retail private convention;
// mode and the four payload words are the five stack args (RET 14h).
__declspec(noinline) RecoveryAsciiManager_0043c8b0* __stdcall
RecoveryAscii_Create_0043c8b0(unsigned int draw_priority, unsigned int mode,
    unsigned int payload, unsigned int argument_20,
    unsigned int argument_24, unsigned int argument_28);

// Retail also carries manager in ESI. Native LTCG chooses the private ABI
// from this genuine caller/callee relationship.
__declspec(noinline) void __stdcall RecoveryAscii_Register_0043c970(
    RecoveryAsciiManager_0043c8b0* manager, unsigned int draw_priority,
    unsigned int mode, unsigned int payload, unsigned int argument_20,
    unsigned int argument_24, unsigned int argument_28);
}
