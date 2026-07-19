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
void GameState_SetTimerTarget(unsigned char* state, int owner_value,
                              int target, const float* speed);
void GameState_DisableTimerWithOwner(void* state, int owner);
void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed);
