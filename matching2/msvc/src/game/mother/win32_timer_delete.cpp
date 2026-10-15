#include "th10/source_views/win32_timer_c08c99_0.hpp"
#include "th10/source_views/win32_timer_c08c99_1.hpp"
#include "th10/source_views/win32_timer_c08c99_2.hpp"
#include "th10/source_views/win32_timer_c08c99_3.hpp"
#include "th10/source_views/win32_timer_c08c99_4.hpp"
#include "th10/source_views/win32_timer_c08c99_5.hpp"
#include "th10/source_views/win32_timer_c08c99_6.hpp"
Win32Timer* Win32Timer::Delete(unsigned int flags) {
    Release();
    if (flags & 1) {
        free(this);
    }
    return this;
}
