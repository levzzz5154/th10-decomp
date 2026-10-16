#include "th10/source_views/window_exact_0.hpp"
#include "th10/source_views/window_exact_1.hpp"
int __stdcall SaveSystemSettingsRetail2() {
    SystemParametersInfoA(0x10, 0, &g_screen_saver_active, 0);
    SystemParametersInfoA(0x53, 0, &g_screen_saver_timeout, 0);
    SystemParametersInfoA(0x54, 0, &g_monitor_power_off, 0);
    SystemParametersInfoA(0x11, 0, 0, 2);
    SystemParametersInfoA(0x55, 0, 0, 2);
    SystemParametersInfoA(0x56, 0, 0, 2);
    QueryPerformanceFrequency((long long*)&g_qpc_frequency);
    return QueryPerformanceCounter((long long*)&g_qpc_previous);
}
