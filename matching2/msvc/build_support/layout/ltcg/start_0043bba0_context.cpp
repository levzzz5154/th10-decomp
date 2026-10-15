// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0043bba0.cpp"
extern "C" unsigned long __stdcall WaitForSingleObject_0043bba0(void*, unsigned long);
#pragma code_seg(".text$03anchor")
__declspec(noinline) void PlatformWorker_0043bba0::Stop() {
    if (thread) {
        stop_requested = 1;
        running = 0;
        while (WaitForSingleObject_0043bba0(thread, 200) == 258) {
            stop_requested = 1;
            running = 0;
        }
        thread = 0;
        entry = 0;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StartContext_0043bba0(int count) {
    int total = 0;
    while (count--) { StartWorker_0043bba0(); total += count; }
    return total;
}
#pragma code_seg()
