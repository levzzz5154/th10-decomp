#pragma once

#include "th10/platform/windows_types.hpp"

// Retail timer object torn down during game shutdown: a multimedia
// timeSetEvent/timer period pair behind the vtable at 0x0046F810.
struct TimerWin32 {
    void** vtable;    // +0x00 class vtable
    UINT timer_id;    // +0x04 active timeSetEvent identifier, 0 when idle
    UINT period;      // +0x08 timeBeginPeriod resolution in milliseconds
};

void TimerWin32_Release(TimerWin32* timer, void* vtable);
