#include "th10/game/recovery_emitter_state.hpp"

extern "C" unsigned int data_00474e30;
extern "C" unsigned int data_00491fb8;
extern "C" unsigned int data_00491ff4;

#pragma code_seg(".text$01decision")
// 0x0040B9F0: update the emitter's decision, returning 1 or 6.
__declspec(noinline) int
RecoveryUpdateEmitterState_0040b9f0::UpdateEmitterDecision() {
    RecoveryTickState_0040bd20* tick_state = this->tick_state_018;

    if (TickRecoveryState_0040bd20(tick_state) != 0) {
        // Retail's NEG/SBB/AND/ADD sequence selects 2 when the 0x1000 input
        // flag is set and 15 otherwise.
        data_00491fb8 = (data_00491ff4 & 0x1000u) ? 2u : 15u;
        return 1;
    }

    // INC in the retail body wraps as a signed 32-bit operation. Spell the
    // wrap without invoking C++ signed-overflow behavior.
    unsigned int next_count_bits =
        static_cast<unsigned int>(this->decision_counter_024) + 1u;
    int next_count;
    if (next_count_bits <= 0x7fffffffu) {
        next_count = static_cast<int>(next_count_bits);
    } else {
        next_count = -1 - static_cast<int>(~next_count_bits);
    }
    this->decision_counter_024 = next_count;

    const unsigned int tick_flags = tick_state->flags_074;
    if ((tick_flags & 0x04u) != 0 ||
        (this->flags_020 & 0x02u) != 0 ||
        (tick_flags & 0x02u) == 0 ||
        (data_00474e30 & 0x100u) == 0) {
        return 1;
    }

    return next_count % 12 == 0 ? 6 : 1;
}
#pragma code_seg()
