#include "th10/source_views/window_exact_0.hpp"
#include "th10/source_views/window_exact_1.hpp"
int __stdcall SaveSystemSettingsRetail_004392e0() {
    SystemParametersInfoA(0x10, 0, &data_0049251c, 0);
    SystemParametersInfoA(0x53, 0, &data_00492520, 0);
    SystemParametersInfoA(0x54, 0, &data_00492524, 0);
    SystemParametersInfoA(0x11, 0, 0, 2);
    SystemParametersInfoA(0x55, 0, 0, 2);
    SystemParametersInfoA(0x56, 0, 0, 2);
    QueryPerformanceFrequency((long long*)&data_00492508);
    return QueryPerformanceCounter((long long*)&data_00492510);
}
