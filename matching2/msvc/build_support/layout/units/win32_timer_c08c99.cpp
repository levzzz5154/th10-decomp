#include "th10/source_views/win32_timer_c08c99_0.hpp"
__forceinline void Win32Timer::Finish() {
    vtable = &g_win32_timer_vtable;
    Cancel();
    // Both original cleanup bodies release the period a second time.
    timeEndPeriod(caps.minimum_period);
}
#include "th10/source_views/win32_timer_c08c99_1.hpp"
#include "../../../src/core/midilib/win32_timer_construct.cpp"
#include "th10/source_views/win32_timer_c08c99_2.hpp"
#include "../../../src/game/mother/win32_timer_release.cpp"
#include "th10/source_views/win32_timer_c08c99_3.hpp"
#include "../../../src/core/midilib/win32_timer.cpp"
#include "th10/source_views/win32_timer_c08c99_6.hpp"
#include "../../../src/game/mother/win32_timer_delete.cpp"

#pragma code_seg()
