#pragma once

struct RecoveryTickState_0040bd20 {
    int pad_000;
    int previous_004;
    int current_008;
    float elapsed_00c;
    const float* speed_010;
    unsigned char reserved_014[0x74 - 0x14];
    unsigned int flags_074;
};

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

typedef char RecoveryTickState_0040bd20_must_be_78[
    sizeof(RecoveryTickState_0040bd20) == 0x78 ? 1 : -1];
typedef char RecoveryUpdateEmitterState_0040b9f0_must_be_28[
    sizeof(RecoveryUpdateEmitterState_0040b9f0) == 0x28 ? 1 : -1];
typedef char RecoveryEmitterState_requires_x86_pointers[
    sizeof(void*) == 4 ? 1 : -1];
