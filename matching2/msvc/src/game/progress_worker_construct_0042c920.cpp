// 0x0042C920: construct the object published at 0x0047784C (vtable 0x0046ECF0).
#include "th10/game/anm_vm.hpp"
#include "th10/game/counter_block.hpp"

extern "C" const void* const data_0046ecf0[];

// The vtable pointer, set before any member is constructed.
struct ProgressWorkerBase_0042c920 {
    const void* const* vtable;

    __forceinline ProgressWorkerBase_0042c920() { vtable = data_0046ecf0; }
};

// A state word whose low bit is cleared on construction.
struct BusyFlag_0042c920 {
    unsigned int busy : 1;
    unsigned int other_flags : 31;

    __forceinline BusyFlag_0042c920() { busy = 0; }
};

struct ProgressWorker_0042c920 : ProgressWorkerBase_0042c920 {
    unsigned int flags;
    unsigned char unknown_008[0x1C];
    CounterBlock first_counter;
    CounterBlock second_counter;
    CounterBlock third_counter;
    unsigned char unknown_2ac[0x14];
    BusyFlag_0042c920 state;
    unsigned char unknown_2c4[0x5630];
    CounterBlock total_counter;
    unsigned char unknown_59cc[0xE4];
    GameTimer timer;
    unsigned char unknown_5ac4[8];

    ProgressWorker_0042c920();
};
extern "C" ProgressWorker_0042c920* data_0047784c;

#pragma code_seg(".text$01accessor")
__declspec(noinline) ProgressWorker_0042c920::ProgressWorker_0042c920() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_0047784c = this;
}
#pragma code_seg()
