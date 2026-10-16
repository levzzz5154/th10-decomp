// 0x00439660..0x004396F7 (152 bytes) - frame timer sample, retail sub_439660.
//
// Returns the frame time relative to the shortest interval seen so far: the
// performance counter delta over the counter frequency when a frequency is
// available, otherwise the millisecond tick count scaled to seconds. The
// running minimum at 0x00492540 is lowered first, so the result is always
// measured against the fastest frame observed since startup.

extern "C" {
extern long long g_qpc_frequency;  // 0x00492508: QueryPerformanceFrequency value
extern long long g_qpc_previous;  // 0x00492510: counter value at startup
extern double g_frame_min_delta;     // 0x00492540: shortest interval seen so far

__declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* count);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int period);
}

double FrameTimer_Sample(void) {
    double elapsed;
    if (g_qpc_frequency != 0) {
        long long mark;
        QueryPerformanceCounter(&mark);
        elapsed = (double)(mark - g_qpc_previous) / (double)g_qpc_frequency;
    } else {
        timeBeginPeriod(1);
        elapsed = (double)timeGetTime();
        timeEndPeriod(1);
        elapsed *= 0.001;
    }
    if (g_frame_min_delta > elapsed) {
        g_frame_min_delta = elapsed;
    }
    return elapsed - g_frame_min_delta;
}
