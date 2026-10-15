#include <stddef.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" int g_globals_gauge;
extern "C" float g_game_speed;

struct SpellTimerDisplay {
    unsigned char reserved_0000[0x9ec0];
    int remaining_seconds;           // +0x9EC0
};

typedef char SpellTimerDisplay_004127a0_seconds_offset_check[
    offsetof(SpellTimerDisplay, remaining_seconds) == 0x9ec0 ? 1 : -1];

extern "C" SpellTimerDisplay *g_front;

struct SpellTimerStage {
    unsigned char reserved_0000[0xad4];
    unsigned int flag_ad4;
    unsigned char reserved_0ad8[0x3a8];
    unsigned int flag_e80;
    unsigned char reserved_0e84[0x754];
    unsigned int flag_15d8;
    unsigned char reserved_15dc[0x3a8];
    unsigned int flag_1984;
    unsigned char reserved_1988[0x3a8];
    unsigned int flag_1d30;
    unsigned char reserved_1d34[0x3a8];
    unsigned int flag_20dc;
    unsigned char reserved_20e0[0x3a8];
    unsigned int flag_2488;
    unsigned char reserved_248c[0x12ac];
    int invuln_timer;
    unsigned char reserved_373c[0x50];
    unsigned int flags;
    unsigned int charge;
};

extern "C" SpellTimerStage *g_card;

struct SpellTimerClock {
    int previous_frame;              // +0x00
    int current_frame;               // +0x04
    float elapsed;                   // +0x08
    const float *speed;               // +0x0C
    unsigned int flags;               // +0x10
    __forceinline void Reset() {
        if ((flags & 1u) == 0) {
            current_frame = 0;
            previous_frame = -999999;
            elapsed = 0.0f;
            speed = &g_game_speed;
            flags |= 1u;
        }
        current_frame = 0;
        elapsed = 0.0f;
        previous_frame = -1;
    }
};

typedef char SpellTimerClock_004127a0_size_check[
    sizeof(SpellTimerClock) == 0x14 ? 1 : -1];

struct SpellTimerSlot {
    int spell_id;                     // +0x00
    int due_frame;                    // +0x04
    void *armed_resource;             // +0x08, returned by the active-id path
    void *due_resource;               // +0x0C, returned by the deadline path
};

typedef char SpellTimerSlot_004127a0_size_check[
    sizeof(SpellTimerSlot) == 0x10 ? 1 : -1];

struct SpellTimerState {
    unsigned char reserved_0000[0x1158];
    SpellTimerClock clock;
    unsigned char reserved_116c[0x1290];
    int active_spell_id;              // +0x23FC
    unsigned char reserved_2400[4];
    int last_spell_delta;             // +0x2404
    unsigned char reserved_2408[0x78];
    unsigned int state_flags;         // +0x2480
    unsigned char reserved_2484[0x10];
    SpellTimerSlot slots[8];  // +0x2494
    void *AdvanceSlots();
};

typedef char SpellTimerState_004127a0_timer_offset_check[
    offsetof(SpellTimerState, clock) == 0x1158 ? 1 : -1];
typedef char SpellTimerState_004127a0_slots_offset_check[
    offsetof(SpellTimerState, slots) == 0x2494 ? 1 : -1];
typedef char SpellTimerState_004127a0_active_id_offset_check[
    offsetof(SpellTimerState, active_spell_id) == 0x23fc ? 1 : -1];
typedef char SpellTimerState_004127a0_delta_offset_check[
    offsetof(SpellTimerState, last_spell_delta) == 0x2404 ? 1 : -1];
typedef char SpellTimerState_004127a0_flags_offset_check[
    offsetof(SpellTimerState, state_flags) == 0x2480 ? 1 : -1];

// 0x004127A0..0x004129F0: advance the first armed spell timer, or the first
// positive deadline that has not yet been retired. Ghidra identifies an
// ECX receiver and an EAX result; callers use that contract
// directly without stack arguments.
#pragma code_seg(".text$01accessor")
__declspec(noinline) void *SpellTimerState::AdvanceSlots() {
    SpellTimerState *self = this;
    unsigned int slot_index;

    for (slot_index = 0; slot_index < 8; ++slot_index) {
        if (self->slots[slot_index].spell_id >= 0) {
            self->last_spell_delta = self->active_spell_id - self->slots[slot_index].spell_id;
            if (self->active_spell_id <= self->slots[slot_index].spell_id) {
                self->active_spell_id = self->slots[slot_index].spell_id;
                self->slots[slot_index].spell_id = -1;

                self->clock.Reset();
                self->state_flags &= ~0x00010000u;
                return self->slots[slot_index].armed_resource;
            }
            break;
        }
    }

    slot_index = 0;
    do {
        if (self->slots[slot_index].spell_id >= 0 && self->slots[slot_index].due_frame > 0)
            break;
        ++slot_index;
        if (slot_index >= 8)
            goto no_resource;
    } while (true);

    {
        int seconds_remaining =
            (self->slots[slot_index].due_frame - self->clock.current_frame + 59) / 60;
        if (seconds_remaining > 99)
            seconds_remaining = 99;

        SpellTimerDisplay *timer_display = g_front;
        timer_display->remaining_seconds = seconds_remaining;
        if (self->clock.current_frame < self->slots[slot_index].due_frame)
            goto no_resource;

        self->active_spell_id = self->slots[slot_index].spell_id;
        self->slots[slot_index].spell_id = -1;
        self->clock.Reset();
        self->state_flags |= 0x00010000u;

        int &countdown = g_globals_gauge;
        countdown -= 3000;
        if (countdown < 5000)
            countdown = 5000;

        SpellTimerStage *stage_state = g_card;
        unsigned int *stage_flags = &stage_state->flags;
        unsigned int saved_stage_flags = *stage_flags;
        if ((saved_stage_flags & 8u) == 0 &&
            stage_state->invuln_timer >= 60) {
            stage_state->charge = 0;
            // Preserve the charge store before the flag-clearing schedule.
            // This compiler intrinsic emits no instructions.
            _ReadWriteBarrier();
            *stage_flags = saved_stage_flags & ~2u;
            stage_state->flag_ad4 &= ~2u;
            stage_state->flag_e80 &= ~2u;
            stage_state->flag_15d8 &= ~2u;
            stage_state->flag_1984 &= ~2u;
            stage_state->flag_1d30 &= ~2u;
            stage_state->flag_20dc &= ~2u;
            stage_state->flag_2488 &= ~2u;
        }

        return self->slots[slot_index].due_resource;
    }
no_resource:
    return 0;
}

#pragma code_seg()
