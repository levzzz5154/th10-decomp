#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

// Complete 0x0040AC90. The two real source inputs are the input state and
// selected mode; native LTCG derives the private EAX state receiver.
#pragma code_seg(".text$0040ac90_fn")
void SetInputMode(DispatcherInputState* state, int mode) {
    if (!(state->flags & 0x1000))
        state->mode = mode;
    else
        state->mode = 2;
}
#pragma code_seg()

