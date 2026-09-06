// =============================================================================
// timer.hpp - Retail five-word frame timer
// =============================================================================
#pragma once

struct FrameTimer {
    int previous;                 // +0x00
    int current;                  // +0x04
    float elapsed;                // +0x08
    const float* speed;           // +0x0C
    unsigned int flags;           // +0x10
};

struct EmbeddedTimerState {
    int target;
    int current;
    int previous;
    const float* speed;
    unsigned int flags;
};

void FrameTimer_Tick(FrameTimer* timer);
void FrameTimer_Advance(FrameTimer* timer, float delta);
void FrameTimer_Decrement(FrameTimer* timer, int count);

// Defined in src/math/math_utils.cpp. Both install the shared time scale and
// the initialized bit on first use, then overwrite the sentinel they just
// wrote; callers such as 0x0040D280 and 0x00415B00 reuse them directly.
void Timer_Set(FrameTimer* timer, int target);
void Timer_Reset(FrameTimer* timer);
// Raw PE32 owner layout; the embedded speed pointer occupies four bytes.
void GameState_SetTimerTarget(unsigned char* state, int owner_value);
void GameState_DisableTimerWithOwner(void* state, int owner);
void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed);
