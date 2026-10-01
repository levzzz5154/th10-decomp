// 0x00428160 and 0x004281D0: the stage sequence's periodic schedule.
//
// Update runs the sequence timer while the sequence is active. Each new frame
// is offered to the schedule selected by the current rank, and the timer wraps
// after fifteen frames. Compiled in the frame_timer native-LTCG cluster, which
// keeps the sequence in EAX for Update and in EDI for Dispatch (with the frame
// in EBX) and gives the timer helpers their private receivers.
//
// Two source shapes are load-bearing for the retail bytes: the repeat flag is
// a bitfield (that is what keeps the constant 1 in EBX), and the frame-changed
// test is an inline helper (so the dispatched frame is read again from the
// timer rather than reused from the comparison).
#include "th10/game/stage_schedule.hpp"

// The timer store at 0x00405410 takes the timer in EAX.
struct PlayerSchedulerRecord {
    void SetSchedulerValue(int value);
};

extern "C" {
int __stdcall StageSchedule_Fire_00427e90(StageSequence* sequence,
                                          StageScheduleEntry* entry, int frame);
extern unsigned short data_00474c48;     // rank counter, twenty steps per rank
extern struct {
    unsigned int repeat : 1;             // the schedule wraps instead of stopping
} data_00474e5c;
}

#pragma code_seg(".text$04zzm_dispatch")
int StageSequence::Dispatch(int frame) {
    int rank = data_00474c48 / 20;
    if (rank >= 5)
        rank = 4;
    if (alternate)
        rank += 5;
    for (StageScheduleEntry* entry = file->schedules[rank].entries;
         entry->period >= 0; ++entry) {
        if (frame % entry->period == entry->phase)
            StageSchedule_Fire_00427e90(this, entry, frame);
    }
    return 0;
}

// True on the first update of a new frame.
static inline bool TimerChanged(const FrameTimer& timer) {
    return timer.current != timer.previous;
}

#pragma code_seg(".text$04zzn_update")
int StageSequence::Update() {
    if (running == 1) {
        if (timer.current < 0) {
            if (!data_00474e5c.repeat)
                return 0;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer)->SetSchedulerValue(0);
        }
        if (TimerChanged(timer))
            Dispatch(timer.current);
        if (timer.current >= 15) {
            if (data_00474e5c.repeat)
                timer.Advance(-15.0f);
            else
                reinterpret_cast<PlayerSchedulerRecord*>(&timer)->SetSchedulerValue(-1);
            return 0;
        }
        timer.Tick();
        return 0;
    }
    pending_3504 = 0;
    pending_name_3508 = 0;
    return 0;
}
#pragma code_seg()
