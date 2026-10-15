#pragma once



// 0x004392E0..0x00439343: SaveSystemSettingsRetail
// Apply the six system parameters the game needs before its message loop runs
// and start the performance counters the frame clock reads. The API is reached
// through its import slot six times, so the compiler keeps the loaded entry
// point in ESI across every call.
extern "C" __declspec(dllimport) int __stdcall SystemParametersInfoA(
    unsigned int action, unsigned int param, void* value, unsigned int flags);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(
    long long* frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(
    long long* count);

