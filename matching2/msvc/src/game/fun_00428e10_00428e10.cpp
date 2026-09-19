// 0x00428E10..0x00428E62 (83 bytes): republish the boss gauge from a record.
//
// Retail enters this member with the score state in EAX and the two counters in
// ECX, a pair no C++ declaration can name, so the body is compiled in the
// native-LTCG cluster layout/ltcg/score_gauge_publish_00428e10.json, whose
// array-walking synthetic caller establishes it.  The body itself is ordinary
// readable C++.
//
// The state is the manager the neighbouring gauge update (0x00428C20,
// src/game/boss_gauge.cpp) reads: it owns the 152-byte gauge slots.  This entry
// parks the record's two counters at +0x3CC/+0x3D0, republishes them as the
// gauge position at +0x3C0/+0x3C4 scaled to playfield units (0.01 per unit) and
// marks the first four slots.
//
// The counters are written through one shared base pointer.  Without it the
// backend hoists the first `fild` above the second counter store and fills the
// x87 latency slot with its own schedule, moving 53 of the 83 bytes; with it the
// stores stay adjacent and retail's `mov ecx,1` lands in the `fild`/`fmul`
// slot.  The four slots are marked by a loop: the unrolled result is retail's
// four constant-offset stores, while four explicit assignments schedule those
// stores into the x87 latency slots.

struct ScoreCounters_00428e10 {
    int value;                       // +0x00
    int maximum;                     // +0x04
};

struct ScoreSlot_00428e10 {          // stride 0x98
    unsigned char pad_000[0x50];
    int flag;                        // +0x50
    unsigned char pad_054[0x44];
};

struct ScoreState_00428e10 {
    unsigned char pad_000[0x3C0];
    float position_x;                // +0x3C0
    float position_y;                // +0x3C4
    int field_3c8;                   // +0x3C8
    int counter_value;               // +0x3CC
    int counter_maximum;             // +0x3D0
    unsigned char pad_3d4[0x2F08];
    ScoreSlot_00428e10 slots[4];     // +0x32DC

    __declspec(noinline) ScoreState_00428e10* SetBossGauge(const ScoreCounters_00428e10* source);
};

typedef char ScoreState_00428e10_size_must_fit[
    sizeof(ScoreState_00428e10) == 0x32DC + 4 * 0x98 ? 1 : -1];

#pragma code_seg(".text$01accessor")
ScoreState_00428e10* ScoreState_00428e10::SetBossGauge(const ScoreCounters_00428e10* source) {
    int* counters = &counter_value;
    counters[0] = source->value;
    counters[1] = source->maximum;
    position_x = (float)counter_value * 0.01f;
    position_y = (float)counter_maximum * 0.01f;
    for (int i = 0; i < 4; i++) {
        slots[i].flag = 1;
    }
    return this;
}
#pragma code_seg()
