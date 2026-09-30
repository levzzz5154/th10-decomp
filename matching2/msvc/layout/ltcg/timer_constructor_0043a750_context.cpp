// Synthetic array-construction compiler context only; never recovered code.
#include "../../src/unidentified/unassigned_0043a750.cpp"

inline void* __cdecl operator new(unsigned int, void* memory) { return memory; }
inline void __cdecl operator delete(void*, void*) {}

#pragma code_seg(".text$03context")
int __stdcall DerivedTimerCompilerContext(DerivedTimerState* timers, int count) {
    for (int index = 0; index < count; ++index) {
        new (&timers[index]) DerivedTimerState;
    }
    return 0;
}
#pragma code_seg()
