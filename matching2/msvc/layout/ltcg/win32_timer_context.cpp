// Compiler context only; none of this caller or its allocation helpers enters
// the recovered image. Shared uses let native LTCG choose the internal ABI.
#pragma code_seg(".text$B0context")
#include "../../src/platform/win32_timer.cpp"

#pragma code_seg(".text$B0context")
inline void* __cdecl operator new(unsigned int, void* memory) {
    return memory;
}

inline void __cdecl operator delete(void*, void*) {
}

// MSVC requests its implicit deleting destructor before discarding it.
inline void __cdecl operator delete(void* memory) {
    free(memory);
}

#pragma code_seg(".text$B0context")
void __stdcall Win32TimerCompilerContext(Win32Timer* timers, int count,
                                         unsigned int delay,
                                         Win32TimerCallback callback,
                                         unsigned int user, unsigned int flags) {
    for (int index = 0; index < count; ++index) {
        new (&timers[index]) Win32Timer;
        timers[index].Start(delay, callback, user);
        timers[index].Stop();
        timers[index].Release();
        timers[index].~Win32Timer();
        if (flags) {
            timers[index].Delete(flags);
        }
    }
}
#pragma code_seg()
