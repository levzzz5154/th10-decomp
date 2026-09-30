#include "th10/game/recovery_emitter_decision_0040b9f0.hpp"

extern "C" unsigned int data_00474e30;
extern "C" unsigned int data_00491fb8;
extern "C" unsigned int data_00491ff4;

// Compiler-only anchor for the private receiver convention used by the
// callback. This C++ model is not selected as recovered game code.
#pragma code_seg(".text$00xdecision")
__declspec(noinline) int
RecoveryUpdateEmitterState_0040b9f0::UpdateEmitterDecision() {
    if (TickRecoveryState_0040bd20(tick_state_018)) {
        data_00491fb8 = (data_00491ff4 & 0x1000u) ? 2u : 15u;
        return 1;
    }

    const int next_count = static_cast<int>(
        static_cast<unsigned int>(decision_counter_024) + 1u);
    decision_counter_024 = next_count;
    const unsigned int tick_flags =
        reinterpret_cast<const RecoveryTickFlagsView_0040b9f0*>(
            tick_state_018)->flags_074;
    int result = next_count;
    if ((tick_flags & 4u) == 0 && (flags_020 & 2u) == 0 &&
        (tick_flags & 2u) != 0 && (data_00474e30 & 0x100u) != 0) {
        const int remainder = result % 12;
        result = 6;
        if (remainder == 0)
            result = 1;
    } else {
        result = 1;
    }
    return result;
}
#pragma code_seg()
