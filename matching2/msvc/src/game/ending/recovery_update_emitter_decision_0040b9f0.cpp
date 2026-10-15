// 0x0040B9F0 (111 bytes): per-frame decision of the ending/credits script
// object. When its script has finished, the next game mode is selected (2 when
// bit 0x1000 of the word at 0x00491FF4 is set, 15 otherwise) and the task
// continues normally (1). Otherwise the frame counter advances; while the
// skip input (bit 0x100 of the input word at 0x00474E30) is held and the
// script allows it, eleven of every twelve frames return 6 so the task is run
// again immediately.
//
// Native LTCG passes the object in EDI and the script state in ESI.
#include "th10/game/recovery_emitter_decision_0040b9f0.hpp"

extern "C" unsigned int data_00474e30;
extern "C" unsigned int data_00491fb8;
extern "C" unsigned int data_00491ff4;

#pragma code_seg(".text$00xdecision")
__declspec(noinline) int
RecoveryUpdateEmitterState_0040b9f0::UpdateEmitterDecision() {
    if (TickRecoveryState_0040bd20(tick_state_018)) {
        data_00491fb8 = (data_00491ff4 & 0x1000u) ? 2u : 15u;
        return 1;
    }

    ++decision_counter_024;
    const unsigned int tick_flags =
        reinterpret_cast<const RecoveryTickFlagsView_0040b9f0*>(
            tick_state_018)->flags_074;
    if ((tick_flags & 4u) == 0 && (flags_020 & 2u) == 0 &&
        (tick_flags & 2u) != 0 && (data_00474e30 & 0x100u) != 0) {
        if (decision_counter_024 % 12 != 0)
            return 6;
    }
    return 1;
}
#pragma code_seg()
