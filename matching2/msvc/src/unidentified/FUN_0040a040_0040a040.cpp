// 0x0040A040: construct the 0x688-byte state published at 0x004776F8.
#include "th10/game/anm_vm.hpp"
#include "th10/game/counter_block.hpp"

struct CounterState_0040a040 {
    unsigned int flags;
    unsigned char unknown_004[0xC];
    GameTimer timer;
    unsigned char unknown_024[0x18];
    CounterBlock first_counter;
    CounterBlock second_counter;
    CounterBlock third_counter;
    unsigned char unknown_2c4[4];
    AnmVm vm;
    unsigned char unknown_674[0x14];

    CounterState_0040a040();
};
extern "C" CounterState_0040a040* data_004776f8;

#pragma code_seg(".text$01accessor")
__declspec(noinline) CounterState_0040a040::CounterState_0040a040() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_004776f8 = this;
}
#pragma code_seg()
