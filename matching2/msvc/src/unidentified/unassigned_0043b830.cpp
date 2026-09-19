// 0x0043B830..0x0043B83B: sample the high-resolution counter into the global.
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* count);

void Tick_0043b830() {
    QueryPerformanceCounter((long long*)0x497c30);
}
