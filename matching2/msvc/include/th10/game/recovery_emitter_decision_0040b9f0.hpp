#pragma once
#include <stddef.h>

struct RecoveryTickState_0040bd20;
__declspec(noinline) int __stdcall TickRecoveryState_0040bd20(
    RecoveryTickState_0040bd20* state);

struct RecoveryUpdateEmitterState_0040b9f0 {
    unsigned char reserved_000[0x18];
    RecoveryTickState_0040bd20* tick_state_018;
    unsigned char reserved_01c[4];
    unsigned char flags_020;
    unsigned char reserved_021[3];
    int decision_counter_024;

    __declspec(noinline) int UpdateEmitterDecision();
    __declspec(noinline) int RunDecisionCallback();
};

typedef char RecoveryEmitterSizeCheck[
    sizeof(RecoveryUpdateEmitterState_0040b9f0) == 0x28 ? 1 : -1];
typedef char RecoveryEmitterTickOffsetCheck[
    offsetof(RecoveryUpdateEmitterState_0040b9f0, tick_state_018) == 0x18 ? 1 : -1];
typedef char RecoveryEmitterFlagsOffsetCheck[
    offsetof(RecoveryUpdateEmitterState_0040b9f0, flags_020) == 0x20 ? 1 : -1];
typedef char RecoveryEmitterCounterOffsetCheck[
    offsetof(RecoveryUpdateEmitterState_0040b9f0, decision_counter_024) == 0x24 ? 1 : -1];

// Read-only view of the tick object's separately recovered flag word.
struct RecoveryTickFlagsView_0040b9f0 {
    unsigned char reserved_000[0x74];
    unsigned int flags_074;
};
typedef char RecoveryTickFlagsOffsetCheck[
    offsetof(RecoveryTickFlagsView_0040b9f0, flags_074) == 0x74 ? 1 : -1];
