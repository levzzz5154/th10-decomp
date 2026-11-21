// Synthetic array-construction compiler context only; never recovered code.
#include "../../../src/unreferenced/unassigned_43a750.cpp"

inline void* __cdecl operator new(unsigned int, void* memory) { return memory; }
inline void __cdecl operator delete(void*, void*) {}

#pragma code_seg(".text$03context")
int __stdcall DerivedTimerCompilerContext(MidiSequencer* timers, int count) {
    for (int index = 0; index < count; ++index) {
        new (&timers[index]) MidiSequencer;
    }
    return 0;
}
#pragma code_seg()
