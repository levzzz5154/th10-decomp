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

void FrameTimer_Tick(FrameTimer* timer);
