#ifndef TH10_GAME_STAGE_SCHEDULE_HPP
#define TH10_GAME_STAGE_SCHEDULE_HPP

#include <stddef.h>

#include "th10/math/timer.hpp"

// One periodic entry of a stage schedule; a negative period ends the list.
struct StageScheduleEntry {
    signed char period;                  // +0x00
    signed char phase;                   // +0x01
    unsigned char pad_02[0x32];
};

struct StageScheduleSlot {
    StageScheduleEntry* entries;         // +0x00
    int reserved_04;
};

struct StageScheduleFile {
    unsigned char pad_000[0x110];
    StageScheduleSlot schedules[10];     // +0x110: five ranks, then five alternates
};

struct StageSequence {
    unsigned char pad_0000[0x458];
    int running;                         // +0x0458
    StageScheduleFile* file;             // +0x045C
    FrameTimer timer;                    // +0x0460
    unsigned char pad_0474[0x3504 - 0x474];
    int pending_3504;                    // +0x3504
    char pending_name_3508;              // +0x3508
    unsigned char pad_3509[0x4474 - 0x3509];
    int alternate;                       // +0x4474

    __declspec(noinline) int Dispatch(int frame);
    __declspec(noinline) int Update();
};

typedef char StageSequence_timer_offset[offsetof(StageSequence, timer) == 0x460 ? 1 : -1];
typedef char StageSequence_alternate_offset[offsetof(StageSequence, alternate) == 0x4474 ? 1 : -1];
typedef char StageScheduleEntry_size[sizeof(StageScheduleEntry) == 0x34 ? 1 : -1];

#endif
