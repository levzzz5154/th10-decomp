// =============================================================================
// timer.cpp - Readable frame-timer advancement from 0x00404ED0
// =============================================================================
#include "th10/math/timer.hpp"

extern float _DAT_00470afc;      // 1.0f
extern float _DAT_00470b68;      // normal-speed lower bound
extern float _DAT_00470b64;      // normal-speed upper bound
extern float DAT_00476f78;       // default speed (1.0f)


void FrameTimer_Tick(FrameTimer* timer) {
    timer->previous = timer->current;

    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64) {
        ++timer->current;
        timer->elapsed += _DAT_00470afc;
        return;
    }

    timer->elapsed += speed;
    timer->current = (int)timer->elapsed;
}

// 0x0044BF40 / 0x00428DD0 - Advance a timer by an explicit delta while
// retaining the retail previous/current and speed-dependent accumulation.
void FrameTimer_Advance(FrameTimer* timer, float delta) {
    timer->previous = timer->current;
    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64)
        timer->elapsed += delta;
    else
        timer->elapsed += delta * speed;
    timer->current = (int)timer->elapsed;
}

// 0x00428DD0 - Decrement variant used by the replay/input path. Retail
// negates the caller-supplied count and forwards it to 0x0044BF40.
void FrameTimer_Decrement(FrameTimer* timer) {
    FrameTimer_Advance(timer, -1.0f);
}

// 0x0042C620 - Store the owner value and reset the embedded state timer.
void GameState_SetTimerTarget(unsigned char* state, int owner_value,
                              int target, const float* speed) {
    *(int*)(state + 0x20) = owner_value;
    unsigned int* flags = (unsigned int*)(state + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(state + 0x2B4) = 0;
        *(int*)(state + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(state + 0x2B8) = 0;
        *(const float**)(state + 0x2BC) = speed;
        *flags |= 1u;
    }
    *(int*)(state + 0x2B4) = 0;
    *(int*)(state + 0x2B8) = 0;
    *(int*)(state + 0x2B0) = target - 1;
}

// 0x0042C5C0 - Set the timer owner, clear the previous value at +0x20, and
// disable the timer by resetting the target to -1. The default speed pointer
// is wired to the global DAT_00476f78 the first time the sentinel initializes.
void GameState_DisableTimerWithOwner(void* state, int owner) {
    unsigned char* bytes = (unsigned char*)state;
    *(int*)(bytes + 0x1C) = owner;
    *(int*)(bytes + 0x20) = 0;
    unsigned int* flags = (unsigned int*)(bytes + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(bytes + 0x2B4) = 0;
        *(int*)(bytes + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(bytes + 0x2B8) = 0;
        *(const float**)(bytes + 0x2BC) = &DAT_00476f78;
        *flags |= 1u;
    }
    *(int*)(bytes + 0x2B4) = 0;
    *(int*)(bytes + 0x2B8) = 0;
    *(int*)(bytes + 0x2B0) = -1;
}

// 0x004050D0 - Lazily initialize and then disable the embedded timer at the
// +0x30 state offset, preserving the retail sentinel and flag transitions.
void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed) {
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = (int)0xFFF0BDC1;
        timer->previous = 0;
        timer->speed = speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->previous = 0;
    timer->target = -1;
}
