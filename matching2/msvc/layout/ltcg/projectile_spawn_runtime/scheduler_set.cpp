// Compiler context only: the anchor copy of 0x00405410, storing a scheduler
// value into the record whose address the whole-program pass derives (retail
// keeps it in EAX). The anchor bytes are never exported as recovered code.
#include "th10/game/projectile_spawn_runtime_004067d0.hpp"

#pragma code_seg(".text$00405410_s")
void PlayerSchedulerRecord::SetSchedulerValue(int value) {
    if (!(this->flags_10 & 1)) {
        this->field_04 = 0;
        this->field_00 = 0xFFF0BDC1;
        this->field_08 = 0.0f;
        this->field_0C = 0x476F78;
        this->flags_10 |= 1;
    }
    this->field_04 = value;
    this->field_00 = value - 1;
    this->field_08 = (float)value;
}
#pragma code_seg()
