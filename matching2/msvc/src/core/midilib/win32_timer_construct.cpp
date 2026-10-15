#include "th10/source_views/win32_timer_c08c99_0.hpp"
#include "th10/source_views/win32_timer_c08c99_1.hpp"
Win32Timer::Win32Timer() {
    vtable = &g_win32_timer_vtable;
    timeGetDevCaps(&caps, sizeof caps);
    timer_id = 0;
}
