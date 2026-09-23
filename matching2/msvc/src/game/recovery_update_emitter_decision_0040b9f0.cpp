// Semantic model for retail 0x0040B9F0..0x0040BA5E.
//
// Retail receives this object's address in EDI, with no stack arguments. This
// ordinary C++ candidate spells that private receiver as an explicit pointer;
// its entry ABI and generated register schedule have not been reconciled with
// the retail call site. See the focused recovery note.

struct RecoveryTickState_0040bd20;

extern int __stdcall TickRecoveryState_0040bd20(
    RecoveryTickState_0040bd20* state);

extern "C" unsigned int data_00474e30;
extern "C" unsigned int data_00491fb8;
extern "C" unsigned int data_00491ff4;

struct RecoveryUpdateEmitterTickState_0040b9f0 {
    unsigned char reserved_000[0x74];
    unsigned int flags_074;
};

struct RecoveryUpdateEmitterState_0040b9f0 {
    unsigned char reserved_000[0x18];
    RecoveryUpdateEmitterTickState_0040b9f0* tick_state_018;
    unsigned char reserved_01c[4];
    unsigned char flags_020;
    unsigned char reserved_021[3];
    int decision_counter_024;
};

typedef char RecoveryUpdateEmitterTickState_0040b9f0_must_be_78[
    sizeof(RecoveryUpdateEmitterTickState_0040b9f0) == 0x78 ? 1 : -1];
typedef char RecoveryUpdateEmitterState_0040b9f0_must_be_28[
    sizeof(RecoveryUpdateEmitterState_0040b9f0) == 0x28 ? 1 : -1];
typedef char RecoveryUpdateEmitterState_0040b9f0_requires_x86_pointers[
    sizeof(void*) == 4 ? 1 : -1];

// 0x0040B9F0..0x0040BA5E: update the emitter's decision and return 1 or 6.
// The C symbol keeps the old linker name while using a normal C++ signature;
// the private EDI entry convention is not represented by this declaration.
extern "C" __declspec(noinline) int __cdecl
asm_Recovery_UpdateEmitterDecision_0040b9f0(
    RecoveryUpdateEmitterState_0040b9f0* emitter) {
    RecoveryUpdateEmitterTickState_0040b9f0* tick_state =
        emitter->tick_state_018;

    if (TickRecoveryState_0040bd20(
            reinterpret_cast<RecoveryTickState_0040bd20*>(tick_state)) != 0) {
        // Retail's NEG/SBB/AND/ADD sequence selects 2 when the 0x1000 input
        // flag is set and 15 otherwise.
        data_00491fb8 = (data_00491ff4 & 0x1000u) ? 2u : 15u;
        return 1;
    }

    // INC in the retail body wraps as a signed 32-bit operation. Spell the
    // wrap without invoking C++ signed-overflow behavior.
    unsigned int next_count_bits =
        static_cast<unsigned int>(emitter->decision_counter_024) + 1u;
    int next_count;
    if (next_count_bits <= 0x7fffffffu) {
        next_count = static_cast<int>(next_count_bits);
    } else {
        next_count = -1 - static_cast<int>(~next_count_bits);
    }
    emitter->decision_counter_024 = next_count;

    const unsigned int tick_flags = tick_state->flags_074;
    if ((tick_flags & 0x04u) != 0 ||
        (emitter->flags_020 & 0x02u) != 0 ||
        (tick_flags & 0x02u) == 0 ||
        (data_00474e30 & 0x100u) == 0) {
        return 1;
    }

    return next_count % 12 == 0 ? 6 : 1;
}
