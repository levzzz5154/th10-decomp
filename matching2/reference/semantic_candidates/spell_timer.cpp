#include <stddef.h>

extern "C" unsigned char data_00474c4c;
extern "C" unsigned char data_004776f4;
extern "C" unsigned char data_0047770c;

struct SpellTimerClock_004127a0 {
    int previous_frame;              // +0x00
    int current_frame;               // +0x04
    int elapsed;                      // +0x08
    float *speed;                     // +0x0C
    unsigned int flags;               // +0x10
};

typedef char SpellTimerClock_004127a0_size_check[
    sizeof(SpellTimerClock_004127a0) == 0x14 ? 1 : -1];

struct SpellTimerSlot_004127a0 {
    int spell_id;                     // +0x00
    int due_frame;                    // +0x04
    void *armed_resource;             // +0x08, returned by the active-id path
    void *due_resource;               // +0x0C, returned by the deadline path
};

typedef char SpellTimerSlot_004127a0_size_check[
    sizeof(SpellTimerSlot_004127a0) == 0x10 ? 1 : -1];

struct SpellTimerState_004127a0 {
    unsigned char reserved_0000[0x1158];
    SpellTimerClock_004127a0 clock;
    unsigned char reserved_116c[0x1290];
    int active_spell_id;              // +0x23FC
    unsigned char reserved_2400[4];
    int last_spell_delta;             // +0x2404
    unsigned char reserved_2408[0x78];
    unsigned int state_flags;         // +0x2480
    unsigned char reserved_2484[0x10];
    SpellTimerSlot_004127a0 slots[8];// +0x2494
};

typedef char SpellTimerState_004127a0_timer_offset_check[
    offsetof(SpellTimerState_004127a0, clock) == 0x1158 ? 1 : -1];
typedef char SpellTimerState_004127a0_slots_offset_check[
    offsetof(SpellTimerState_004127a0, slots) == 0x2494 ? 1 : -1];
typedef char SpellTimerState_004127a0_active_id_offset_check[
    offsetof(SpellTimerState_004127a0, active_spell_id) == 0x23fc ? 1 : -1];
typedef char SpellTimerState_004127a0_delta_offset_check[
    offsetof(SpellTimerState_004127a0, last_spell_delta) == 0x2404 ? 1 : -1];
typedef char SpellTimerState_004127a0_flags_offset_check[
    offsetof(SpellTimerState_004127a0, state_flags) == 0x2480 ? 1 : -1];

// 0x004127A0..0x004129F0: advance the first armed spell timer, or the first
// positive deadline that has not yet been retired. Ghidra identifies an
// ECX-based fastcall receiver and an EAX result; callers use that contract
// directly without stack arguments.
extern "C" __declspec(noinline) void *__fastcall
SpellTimer_AdvanceSlots_004127a0(SpellTimerState_004127a0 *self) {
    unsigned int slot_index;
    SpellTimerSlot_004127a0 *slot;

    for (slot_index = 0; slot_index < 8; ++slot_index) {
        slot = &self->slots[slot_index];
        if (slot->spell_id >= 0) {
            self->last_spell_delta = self->active_spell_id - slot->spell_id;
            if (self->active_spell_id <= slot->spell_id) {
                self->active_spell_id = slot->spell_id;
                slot->spell_id = -1;

                if ((self->clock.flags & 1u) == 0) {
                    self->clock.current_frame = 0;
                    self->clock.previous_frame = -999999;
                    self->clock.elapsed = 0;
                    self->clock.speed = reinterpret_cast<float *>(0x00476f78);
                    self->clock.flags |= 1u;
                }

                self->clock.current_frame = 0;
                self->clock.elapsed = 0;
                self->clock.previous_frame = -1;
                self->state_flags &= ~0x00010000u;
                return slot->armed_resource;
            }
            break;
        }
    }

    for (slot_index = 0; slot_index < 8; ++slot_index) {
        slot = &self->slots[slot_index];
        if (slot->spell_id >= 0 && slot->due_frame > 0)
            break;
    }
    if (slot_index == 8)
        return 0;

    int seconds_remaining =
        (slot->due_frame - self->clock.current_frame + 59) / 60;
    if (seconds_remaining > 99)
        seconds_remaining = 99;

    unsigned char *timer_owner =
        *reinterpret_cast<unsigned char **>(&data_0047770c);
    *reinterpret_cast<int *>(timer_owner + 0x9ec0) = seconds_remaining;
    if (self->clock.current_frame < slot->due_frame)
        return 0;

    self->active_spell_id = slot->spell_id;
    slot->spell_id = -1;
    if ((self->clock.flags & 1u) == 0) {
        self->clock.current_frame = 0;
        self->clock.previous_frame = -999999;
        self->clock.elapsed = 0;
        self->clock.speed = reinterpret_cast<float *>(0x00476f78);
        self->clock.flags |= 1u;
    }

    self->clock.current_frame = 0;
    self->clock.elapsed = 0;
    self->clock.previous_frame = -1;
    self->state_flags |= 0x00010000u;

    int &countdown = *reinterpret_cast<int *>(&data_00474c4c);
    countdown -= 3000;
    if (countdown < 5000)
        countdown = 5000;

    unsigned char *stage_state =
        *reinterpret_cast<unsigned char **>(&data_004776f4);
    unsigned int *stage_flags =
        reinterpret_cast<unsigned int *>(stage_state + 0x378c);
    if ((*stage_flags & 8u) == 0 &&
        *reinterpret_cast<int *>(stage_state + 0x3738) >= 60) {
        *reinterpret_cast<unsigned int *>(stage_state + 0x3790) = 0;
        *reinterpret_cast<unsigned int *>(stage_state + 0x378c) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x0ad4) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x0e80) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x15d8) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x1984) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x1d30) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x20dc) &= ~2u;
        *reinterpret_cast<unsigned int *>(stage_state + 0x2488) &= ~2u;
    }

    return slot->due_resource;
}
