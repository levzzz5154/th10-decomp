// Construct the state published at 0x004776F8.
#include "th10/game/counter_state_0040a040.hpp"

#pragma code_seg(".text$00_ystateinit")
__declspec(noinline) CounterState_0040a040::CounterState_0040a040() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_004776f8 = this;
}
#pragma code_seg()
