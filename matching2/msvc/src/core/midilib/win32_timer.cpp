#include "th10/source_views/win32_timer_c08c99_0.hpp"
#include "th10/source_views/win32_timer_c08c99_1.hpp"
#include "th10/source_views/win32_timer_c08c99_2.hpp"
#include "th10/source_views/win32_timer_c08c99_3.hpp"
Win32Timer::~Win32Timer() {
    Finish();
}


#include "../../../include/th10/source_views/win32_timer_c08c99_4.hpp"
#include "th10/source_views/win32_timer_c08c99_0.hpp"
#include "th10/source_views/win32_timer_c08c99_1.hpp"
#include "th10/source_views/win32_timer_c08c99_2.hpp"
#include "th10/source_views/win32_timer_c08c99_3.hpp"
#include "th10/source_views/win32_timer_c08c99_4.hpp"
unsigned int Win32Timer::Start(unsigned int delay, Win32TimerCallback callback,
                              unsigned int user) {
    Cancel();
    timeBeginPeriod(caps.minimum_period);
    const unsigned int periodic = 1;
    if (callback) {
        timer_id = timeSetEvent(delay, caps.minimum_period, callback, user, periodic);
    } else {
        timer_id = timeSetEvent(delay, caps.minimum_period,
                               reinterpret_cast<Win32TimerCallback>(&MidiTimer_Callback),
                               reinterpret_cast<unsigned int>(this), periodic);
    }
    return timer_id;
}


#include "../../../include/th10/source_views/win32_timer_c08c99_5.hpp"
#include "th10/source_views/win32_timer_c08c99_0.hpp"
#include "th10/source_views/win32_timer_c08c99_1.hpp"
#include "th10/source_views/win32_timer_c08c99_2.hpp"
#include "th10/source_views/win32_timer_c08c99_3.hpp"
#include "th10/source_views/win32_timer_c08c99_4.hpp"
#include "th10/source_views/win32_timer_c08c99_5.hpp"
int Win32Timer::Stop() {
    Cancel();
    return 1;
}

